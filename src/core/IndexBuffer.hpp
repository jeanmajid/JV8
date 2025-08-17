#pragma once

class IndexBuffer {
private:
	unsigned int renderer_Id;
	unsigned int count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	inline unsigned int getCount() const {
		return count;
	}
};