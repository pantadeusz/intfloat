#include <iostream>
#include <cmath>

class xfloat_t {
	public:
	static const int64_t PRECISION = 100000;
	int64_t data;
	xfloat_t () = default;
	
	xfloat_t ( const xfloat_t & b) {
		data = b.data;
	}
	
	xfloat_t ( const float & b) {
		data = b*(float)PRECISION;
	}
	xfloat_t operator=(float b) {
		data = b*(float)PRECISION;
		return *this;
	}
    operator float() const { return ((float)data)/(float)PRECISION; }
};

xfloat_t operator+(const xfloat_t &a, const xfloat_t &b) {
	xfloat_t ret;
	ret.data = a.data + b.data;
	return ret;
}
xfloat_t operator-(const xfloat_t &a, const xfloat_t &b) {
	xfloat_t ret;
	ret.data = a.data - b.data;
	return ret;
}
xfloat_t operator-(const int64_t a, const xfloat_t &b) {
	xfloat_t ret;
	ret.data = a*xfloat_t::PRECISION - b.data;
	return ret;
}
xfloat_t operator*(const xfloat_t &a, const xfloat_t &b) {
	xfloat_t ret;
	ret.data = (a.data * b.data)/(xfloat_t::PRECISION);
	return ret;
}
xfloat_t operator*(const xfloat_t &a, const int64_t &b) {
	xfloat_t ret;
	ret.data = a.data * b;
	return ret;
}
xfloat_t operator/(const xfloat_t &a, const xfloat_t &b) {
	xfloat_t ret;
	ret.data = a.data*xfloat_t::PRECISION/b.data;//(a.data/xfloat_t::PRECISION) / (b.data/xfloat_t::PRECISION);
	return ret;
}

xfloat_t sin(xfloat_t x) {
	//x − x3/3! + x5/5! − x7/7! 
	xfloat_t ret = x;
	
	xfloat_t poww = x;
	xfloat_t addsub = -1;
	xfloat_t factorial = 1;
	for (int64_t i = 3 ; i < 18; i+=2) {
		factorial = factorial * (i * (i-1));
		poww = poww * x * x;
		ret = ret + addsub*poww/factorial;
		addsub = addsub*(int64_t)(-1);
	}
	return ret;
}

xfloat_t cos(xfloat_t x) {
	const xfloat_t _90 = M_PI/2;
	return sin(_90 - x);
}

int main() {
	xfloat_t value = 100.001;
	float v = value;
	xfloat_t a = 100.4;
	xfloat_t b = 2;
	
	std::cout << value.data << " " << v << std::endl;

	std::cout << ((float)a) << " " << ((float)b) << std::endl;
	std::cout << ((float)(a+b)) << " " << ((float)(a-b)) << std::endl;
	std::cout << ((float)(a*b)) << " " << ((float)(a/b)) << std::endl;
	std::cout << (float)sin((xfloat_t)M_PI) << " " << std::sin(M_PI) << std::endl;
	std::cout << (float)cos((xfloat_t)M_PI) << " " << std::cos(M_PI) << std::endl;
	
	xfloat_t t = 1;
	double tt = 1;
	for (int i = 0; i < 1000; i++) {
		t = operator+(sin(t),(int64_t)1);
		tt = sin(tt)+1;
	}
	std::cout << (float)t << " " << tt << std::endl;
}
