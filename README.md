# JV8

Little Render/Game engine im working on when I have some free time.

Mostly just following tutorials and online resources, trying to learn computer graphics and experimenting with things.
I highly recommend "The Cherno" and his opengl series and this website https://learnopengl.com

Currently only supports opengl and isn't dynamic, meaning alot of stuff is still coded in the main.cpp, im slowly working it out to make it more like an actual library.

# Core concepts

If you see any false information, please correct me, im writing this all out of memory and im not the most active coder. Also if your curious about some of the actual implementations, go into the code base and search, most things are pretty simple.

### Opengl

Opengl unlike others is actually pretty high level. Its a state machine, so you bind some thing and next function call works with that thing you binded before hand. My Renderer shows this pretty well.

```cpp
void Renderer::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) {
	shader.bind();
	vertexArray.bind();
	indexBuffer.bind();

	glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}
```
First we bind all the necessary things and then after we do the draw call. The draw call will then work with all the binded things.

### Vertex

The vertex is a chain of data and can contain many things, like position, color, texture coordinates and whatever you want

```cpp
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f
```

Here we have one vertex with the first 3 floats being the location and the 2 last being the texture coordinates

### Vertex Buffer

The Vertex Buffer is a buffer on your gpu where you store those Vertexes

```cpp
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    ...
}
vertexBuffer = std::make_unique<VertexBuffer>(vertices, 36 * 5 * sizeof(float));
```

### Vertex Array

The Vertex Array defines the structure of an Vertex Buffer, heres how it would look in my [code](src/tests/Test3D.cpp) (line 66)

```cpp
vertexArray = std::make_unique<VertexArray>();
vertexBuffer = std::make_unique<VertexBuffer>(vertices, 36 * 5 * sizeof(float));

vertexBufferLayout = std::make_unique<VertexBufferLayout>();
vertexBufferLayout->push<float>(3);
vertexBufferLayout->push<float>(2);
vertexArray->addBuffer(*vertexBuffer, *vertexBufferLayout);
```
Here we define an layout with 3 floats for the location and 2 for the texture coords.

### Indexes

In opengl we have multiple ways of drawing, but the most common is to use vertexes + indexes

```cpp
glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
```

specifying GL_TRIANGLES means we connect 3 indices to make triangles.

indexes contain numbers and define which vertexes to connect to create triangles.

```cpp
unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
};
```
Here we connect vertex 0, 1, 2 and 2, 3, 0 resulting in 2 triangles.

you can also just let opengl decide and use this call

```cpp
glDrawArrays(GL_TRIANGLES, 0, count);
```

This will connect 0, 1, 2 and 3, 4, 5 and so on, meaning you will probably have double vertexes at some location, which is usually not what you want.

### Index Buffer

Similar to Vertex Buffer, a blob of memory on the gpu that gets used to draw stuff

```cpp
indexBuffer = std::make_unique<IndexBuffer>(indices, 36);
```

### Shaders

Opengl uses glsl as its shading language. Its really similar to C. Shaders are literally just code that runs on your gpu.

Heres the 2 most important shaders:

1. Vertex Shader: Used to transform vertexes and maybe do some math to pass on to other shaders. This shader runs on every vertex.

2. Fragment Shader: Has the task of filling in every pixel in the space between the vertexes, usually triangles. This Shader runs for every pixel.

Shaders can take in data 2 ways

1. Through uniforms

```cpp
shader.setUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

// in shader
uniform vec4 u_Color;
```

2. Through vertex data, which we learned earlier
```cpp
// in shader
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
```

You can look at the Shader [here](res/shaders/basic.shader)

### Model View Projection (MVP)

This is how you transform the world to look either 2d or 3d. Multiplying these 3 matrixes with the location of the vertex, results in a game like enviroment, where you can move around and such. Its really cool.

Model Matrix: This matrix defines how your model is rotated and translated (moved) around the world

View Matrix: This is basically your camera, whatever this matrix is, the world gets moved the oposite, simulating a camera moving around.

Projection Matrix:

This is the most important one, theres 2 types of projection matrixes

1. Ortho:

```cpp
glm::mat4 projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
```

0 to 960.0f and 0 to 540.0f are the screen size in pixels, which will then be converted to -1 to 1 so the gpu can understand, which we call normalised device coordinates.

This is a 2d camera with no sense of depth whatever, no matter how far an object is, it will always be the same size. I used it in [Test2D](src/tests/TestTexture2D.cpp)

2. Perspective:

```cpp
glm::mat4 projection = glm::perspective(
	glm::radians(45.0f),       // Field of view (in radians)
	960.0f / 540.0f,           // Aspect ratio
	0.1f,                      // Near plane (how close to see)
	100.0f                     // Far plane (how far to see)
);
```

3D Camera which has depth. I used it in [Test3D](src/tests/Test3D.cpp)