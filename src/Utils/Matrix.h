#pragma once

template<typename T>
class Matrix {
public:
	Matrix(int width, int height) : width(width), height(height) {
		matrix = new T[width * height];
	}

	T& at(int row, int col) {
		if(!inRange(row, col)) {
			throw "not in range!";
		}

		return matrix[row * width + col];
	}

	bool inRange(int row, int col) {
		return row >= 0 && col >= 0 && row < height && col < width;
	}


	int getCols() {
		return width;
	}

	int getRows() {
		return height;
	}

private:
	int width;
	int height;
	T* matrix;
};


