
enum MatrixType { ZERO, IDENTITY };

template<class T>
class Matrix
{
public:
	Matrix();
	Matrix(size_t i,size_t j, T value);
	Matrix(size_t i,size_t j, MatrixType type);
	T* operator[](size_t i) { return _mat[i];}
	Matrix<T>& operator +(T value);
	Matrix<T>& operator -(T value);
	Matrix<T>& operator *(T value);
	Matrix<T>& operator /(T value);

	Matrix<T>& operator *(Matrix<T> m); 
	inline size_t GetNumRow()	  {return _i;}
	inline size_t GetNumColumn() {return _j;}
protected:
	void Init(T value);
	T **_mat;
	size_t _i,_j;
	
};



///////////////////////////////////////////////////////////////////////////////

template<class T>
Matrix<T>::Matrix()
{
	_mat = new T*[10];
	for ( register size_t i = 0 ; i < 10 ; i++)
		_mat[i] = new T[10];
	
	for (  i = 0 ; i < 10 ; i ++)
		for ( register size_t j = 0 ; j < 10 ; j++)
			_mat[i][j] = 0.0;
}


template<class T>

void Matrix<T>::Init(T value)
{
	_mat = new T*[_j];
	for ( register size_t i = 0 ; i < _j ; i++)
		_mat[i] = new T[_i];
	
	for (  i = 0 ; i < _i ; i ++)
		for ( register size_t j = 0 ; j < _j ; j++)
			_mat[i][j] = value;
}


template<class T>
Matrix<T>::Matrix(size_t i,size_t j, T value)
{
	_i = i;
	_j = j;
	Init(value);
}



template<class T>
Matrix<T>& Matrix<T>::operator +(T value)
{
	for ( register size_t i = 0; i < _i ; i++ )
		for ( register size_t j = 0; j < _j ; j++ ) 
			_mat[i][j] += value;

	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator -(T value)
{
	for ( register size_t i = 0; i < _i ; i++ )
		for ( register size_t j = 0; j < _j ; j++ ) 
			_mat[i][j] -= value;

	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator *(T value)
{
	for ( register size_t i = 0; i < _i ; i++ )
		for ( register size_t j = 0; j < _j ; j++ ) 
			_mat[i][j] *= value;

	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator /(T value)
{
	for ( register size_t i = 0; i < _i ; i++ )
		for ( register size_t j = 0; j < _j ; j++ ) 
			_mat[i][j] /= value;

	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator *(Matrix<T> m)
{
	Matrix<T> *retMat = new Matrix<T>(_i, _j, 0);
	
	for ( register size_t i = 0 ; i < _i ; i++)
		for ( register size_t j = 0 ; j < _j ; j++)
			for ( register size_t k = 0 ; k < _j ; k++ )
				(*retMat)[i][j] += _mat[i][k]*m[k][j];


	return *retMat;
}