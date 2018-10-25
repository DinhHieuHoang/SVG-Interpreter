#pragma once

#include "stdafx.h"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "rapidxml-1.13/rapidxml.hpp"

using namespace std;
using namespace rapidxml;
using namespace Gdiplus;

class Base
{
public:
	virtual ~Base(){}
	virtual void setValue(long long r, long long g, long long b) {}
	virtual void setValue(double x, double y) {}
	virtual void setValue(double x) {}
	virtual void setValue(long long x) {}
	virtual void setValue(string s) {}
	virtual int getSize() { return 0; }
	virtual string getType() = 0;
	virtual Color getColor() { return Color(255, 255, 255); }
	virtual double getDouble() { return 0; }
	virtual string getString() { return ""; }
	virtual pair<double, double> getPair() { return make_pair(0, 0); }
	virtual vector<PointF>& getVector() { vector<PointF>someone; return someone; }
	virtual vector<Base*> getVectorTransform() { vector<Base*> nw; return nw; }
	virtual vector<Base*> getVectorTransformClone() { vector<Base*>nw; return nw; }
	virtual void doTransform(Graphics& graphics) { return; }
	virtual bool getValid() { return false; }
	virtual void setValid(){}
};

class Stroke:public Base
{
public:
	Color _stroke;
	bool valid;
	Stroke()
	{
		_stroke = Color(255, 255, 255);
		valid = false;
	}
	void setValid()
	{
		valid = true;
	}
	bool getValid()
	{
		return valid;
	}
	Color getColor()
	{
		return _stroke;
	}
	string getType()
	{
		return "stroke";
	}
	void setValue(long long r, long long g, long long b)
	{
		valid = true;
		_stroke = Color(r, g, b);
		return;
	}
	void setValue(string s)
	{
		valid = true;
		if (s == "none")
		{
			_stroke = Color(255,255,255);
			valid = false;
			return;
		}
		int lll = 0, rrr = s.length() - 1;
		while (s[lll] == ' ')
			lll++;
		while (s[rrr] == ' ')
			rrr--;
		string slr = s.substr(lll, rrr - lll + 1);
		if (slr == "none")
			return;
		int l = s.length();
		int r=0, g=0, b=0;
		int i = 0;
		for (; i < l; i++)
		{
			if (s[i] >= '0'&&s[i] <= '9')
				break;
		}
		while (i < l&&s[i] >= '0'&&s[i] <= '9')
		{
			r *= 10;
			r += s[i] - '0';
			i++;
		}
		for (; i < l; i++)
		{
			if (s[i] >= '0'&&s[i] <= '9')
				break;
		}
		while (i < l&&s[i] >= '0'&&s[i] <= '9')
		{
			g *= 10;
			g += s[i] - '0';
			i++;
		}
		for (; i < l; i++)
		{
			if (s[i] >= '0'&&s[i] <= '9')
				break;
		}
		while (i < l&&s[i] >= '0'&&s[i] <= '9')
		{
			b *= 10;
			b += s[i] - '0';
			i++;
		}
		setValue(r, g, b);
		return;
	}
};

class Fill:public Base
{
public:
	Color _fill;
	bool valid;
	Fill()
	{
		_fill = Color(0, 0, 0);
		valid = false;
	}
	void setValid()
	{
		valid = true;
	}
	bool getValid()
	{
		return valid;
	}
	Color getColor()
	{
		if(valid)
			return _fill;
		return Color(255, 255, 255);
	}
	string getType()
	{
		return "fill";
	}
	void setValue(long long r, long long g, long long b)
	{
		_fill = Color(r, g, b);
		valid = true;
		return;
	}
	void setValue(string s)
	{
		valid = true;
		if (s == "none")
		{
			valid = false;
			_fill = Color(0, 0, 0);
			return;
		}
		int l = s.length();
		int r = 0, g = 0, b = 0;
		int i = 0;
		for (; i < l; i++)
		{
			if (s[i] >= '0'&&s[i] <= '9')
				break;
		}
		while (i < l&&s[i] >= '0'&&s[i] <= '9')
		{
			r *= 10;
			r += s[i] - '0';
			i++;
		}
		for (; i < l; i++)
		{
			if (s[i] >= '0'&&s[i] <= '9')
				break;
		}
		while (i < l&&s[i] >= '0'&&s[i] <= '9')
		{
			g *= 10;
			g += s[i] - '0';
			i++;
		}
		for (; i < l; i++)
		{
			if (s[i] >= '0'&&s[i] <= '9')
				break;
		}
		while (i < l&&s[i] >= '0'&&s[i] <= '9')
		{
			b *= 10;
			b += s[i] - '0';
			i++;
		}
		setValue(r, g, b);
		return;
	}
};

class StrokeWidth:public Base
{
public:
	double _stroke_width;
	StrokeWidth() :_stroke_width(1){}
	double getDouble()
	{
		return _stroke_width;
	}
	string getType()
	{
		return "stroke-width";
	}
	void setValue(long long x)
	{
		_stroke_width = x;
		return;
	}
	void setValue(string s)
	{
		setValue(stoi(s));
		return;
	}
};

class StrokeOpacity:public Base
{
public:
	double _stroke_opacity;
	StrokeOpacity():_stroke_opacity(1){}
	double getDouble()
	{
		return _stroke_opacity;
	}
	string getType()
	{
		return "stroke-opacity";
	}
	void setValue(double x)
	{
		_stroke_opacity = x;
	}
	void setValue(string s)
	{
		_stroke_opacity = stof(s);
	}
};

class FillOpacity:public Base
{
public:
	double _fill_opacity;
	FillOpacity():_fill_opacity(1){}
	double getDouble()
	{
		return _fill_opacity;
	}
	string getType()
	{
		return "fill-opacity";
	}
	void setValue(double x)
	{
		_fill_opacity = x;
		return;
	}
	void setValue(string s)
	{
		_fill_opacity = stof(s);
		return;
	}
};

class Translate:public Base
{
public:
	pair<double, double> translate;
	Translate():translate(make_pair(0,0)){}
	void doTransform(Graphics& graphics)
	{
		graphics.TranslateTransform(translate.first, translate.second);
	}
	pair<double, double> getPair()
	{
		return translate;
	}
	string getType()
	{
		return "translate";
	}
	void setValue(double x, double y)
	{
		translate = make_pair(x, y);
		return;
	}
	void setValue(string s)
	{
		int l = s.length();
		int i = 0, j = l - 1;
		for (; i < j; i++)
		{
			if (s[i] == '(')
				break;
		}
		i++;
		double x = 0, y = 0;
		int k = i;
		while (s[k] != ',')
			k++;
		string ss = s.substr(i, k - i);
		x = stof(ss);
		k++;
		while (s[l]<'0' || s[l]>'9')
			l--;
		string sss = s.substr(k, l - k + 1);
		y = stof(sss);
		translate = make_pair(x, y);
		return;
	}
};

class Rotate:public Base
{
public:
	double rotate;
	Rotate():rotate(0){}
	void doTransform(Graphics& graphics)
	{
		graphics.RotateTransform((REAL)rotate);
	}
	double getDouble()
	{
		return rotate;
	}
	string getType()
	{
		return "rotate";
	}
	void setValue(double x)
	{
		rotate = x;
	}
	void setValue(string s)
	{
		string s1;
		int l = s.length() - 1;
		int r = 0;
		while (s[r] != '-' && (s[r]<'0'||s[r]>'9'))
			r++;
		while (s[l]<'0' || s[l]>'9')
			l--;
		s1 = s.substr(r, l - r + 1);
		setValue(stof(s1));
		return;
	}
};

class Scale:public Base
{
public:
	pair<double, double> scale;
	Scale() :scale(make_pair(0, 0)){}
	void doTransform(Graphics& graphics)
	{
		graphics.ScaleTransform(scale.first, scale.second);
	}
	pair<double, double> getPair()
	{
		return scale;
	}
	string getType()
	{
		return "scale";
	}
	void setValue(double x, double y)
	{
		scale = make_pair(x, y);
		return;
	}
	void setValue(string s)
	{
		int l = s.length();
		int i = 0, j = l - 1;
		for (; i < j; i++)
		{
			if (s[i] == '(')
				break;
		}
		double x = 0, y = 0;
		for (; i < j; i++)
		{
			if (s[i] == '.' || s[i] == ',')
				break;
			if (s[i] >= '0'&&s[i] <= '9')
			{
				x *= 10;
				x += s[i] - '0';
			}
		}
		if (s[i] == '.')
		{
			double tmp = 0.1;
			i++;
			for (; i < j; i++)
			{
				if (s[i] == ',' || s[i] == ' ')
					break;
				x += tmp*(s[i] - '0');
				tmp *= 0.1;
			}
		}
		i++;
		int ttt = i;
		while (ttt < l)
		{
			if (s[ttt] >= '0'&&s[ttt] <= '9')
				break;
			ttt++;
		}
		if (ttt == l)
		{
			scale = make_pair(x, x);
			return;
		}
		for (; i < j; i++)
		{
			if (s[i] == '.' || s[i] == ',')
				break;
			if (s[i] >= '0'&&s[i] <= '9')
			{
				y *= 10;
				y += s[i] - '0';
			}
		}
		if (i<l&&s[i] == '.')
		{
			double tmp = 0.1;
			i++;
			for (; i < j; i++)
			{
				if (s[i] == ',' || s[i] == ' ')
					break;
				y += tmp*(s[i] - '0');
				tmp *= 0.1;
			}
		}
		scale = make_pair(x, y);
		return;
	}
};

class Transform:public Base
{
public:
	vector<Base*> transform;
	~Transform()
	{
		int i = transform.size();
		while (i--)
		{
			delete transform[i];
		}
		transform.clear();
	}
	int getSize()
	{
		return transform.size();
	}
	vector<Base*> getVectorTransform()
	{
		return transform;
	}
	vector<Base*> getVectorTransformClone()
	{
		return transform;
	}
	string getType()
	{
		return "transform";
	}
	void setValue(string s)
	{
		int l = s.length();
		int i = 0, j = 0;
		while (s[j] != ')')
			j++;
		string s1 = s.substr(i, j - i + 1);
		int i1 = 0, j1 = 0;
		while (s1[i1]<'a' || s[i1]>'z')
			i1++;
		j1 = i1;
		while (s1[j1 + 1] >= 'a'&&s1[j1 + 1] <= 'z')
			j1++;
		string tmp = s1.substr(i1, j1 - i1 + 1);
		if (tmp == "translate")
		{
			Base* nw = new Translate;
			nw->setValue(s1);
			transform.push_back(nw);
		}
		else if (tmp == "rotate")
		{
			Base* nw = new Rotate;
			nw->setValue(s1);
			transform.push_back(nw);
		}
		else if (tmp == "scale")
		{
			Base* nw = new Scale;
			nw->setValue(s1);
			transform.push_back(nw);
		}
		while (j < l - 1)
		{
			i = j + 1;
			j = i;
			while (j < l&&s[j] != ')')
				j++;
			if (j == l)
				return;
			s1 = s.substr(i, j - i + 1);
			i1 = 0; j1 = 0;
			while (s1[i1]<'a' || s[i1]>'z')
				i1++;
			j1 = i1;
			while (s1[j1 + 1] >= 'a'&&s1[j1 + 1] <= 'z')
				j1++;
			tmp = s1.substr(i1, j1 - i1 + 1);
			if (tmp == "translate")
			{
				Base* nw = new Translate;
				nw->setValue(s1);
				transform.push_back(nw);
			}
			else if (tmp == "rotate")
			{
				Base* nw = new Rotate;
				nw->setValue(s1);
				transform.push_back(nw);
			}
			else if (tmp == "scale")
			{
				Base* nw = new Scale;
				nw->setValue(s1);
				transform.push_back(nw);
			}
		}
		return;
	}
};

class PointAx :public Base
{
public:
	double x1;
	PointAx() :x1(0){}
	double getDouble()
	{
		return x1;
	}
	string getType()
	{
		return "x1";
	}
	void setValue(double x)
	{
		x1 = x;
		return;
	}
	void setValue(string s)
	{
		setValue(stof(s));
		return;
	}
};

class PointAy :public Base
{
public:
	double y1;
	PointAy() :y1(0) {}
	double getDouble()
	{
		return y1;
	}
	string getType()
	{
		return "y1";
	}
	void setValue(double x)
	{
		y1 = x;
		return;
	}
	void setValue(string s)
	{
		setValue(stof(s));
		return;
	}
};

class PointBx :public Base
{
public:
	double x2;
	PointBx() :x2(0) {}
	double getDouble()
	{
		return x2;
	}
	string getType()
	{
		return "x2";
	}
	void setValue(double x)
	{
		x2 = x;
		return;
	}
	void setValue(string s)
	{
		setValue(stof(s));
		return;
	}
};

class PointBy :public Base
{
public:
	double y2;
	PointBy() :y2(0) {}
	double getDouble()
	{
		return y2;
	}
	string getType()
	{
		return "y2";
	}
	void setValue(double x)
	{
		y2 = x;
		return;
	}
	void setValue(string s)
	{
		setValue(stof(s));
		return;
	}
};

class PointX:public Base
{
public:
	double x;
	PointX() :x(0) {}
	double getDouble()
	{
		return x;
	}
	string getType()
	{
		return "x";
	}
	void setValue(double x)
	{
		this->x = x;
		return;
	}
	void setValue(string s)
	{
		setValue(stof(s));
		return;
	}
};

class PointY:public Base
{
public:
	double y;
	PointY() :y(0) {}
	double getDouble()
	{
		return y;
	}
	string getType()
	{
		return "y";
	}
	void setValue(double x)
	{
		y = x;
		return;
	}
	void setValue(string s)
	{
		setValue(stof(s));
		return;
	}
};

class CenterX :public Base
{
public:
	double cx;
	CenterX() :cx(0) {}
	double getDouble()
	{
		return cx;
	}
	string getType()
	{
		return "cx";
	}
	void setValue(double x)
	{
		cx = x;
		return;
	}
	void setValue(string s)
	{
		setValue(stof(s));
		return;
	}
};

class CenterY :public Base
{
public:
	double cy;
	CenterY() :cy(0) {}
	double getDouble()
	{
		return cy;
	}
	string getType()
	{
		return "cy";
	}
	void setValue(double x)
	{
		cy = x;
		return;
	}
	void setValue(string s)
	{
		setValue(stof(s));
		return;
	}
};

class Width :public Base
{
public:
	double _width;
	Width() :_width(0) {}
	double getDouble()
	{
		return _width;
	}
	string getType()
	{
		return "width";
	}
	void setValue(double x)
	{
		_width = x;
		return;
	}
	void setValue(string s)
	{
		setValue(stof(s));
		return;
	}
};

class Height :public Base
{
public:
	double _height;
	Height() :_height(0) {}
	double getDouble()
	{
		return _height;
	}
	string getType()
	{
		return "height";
	}
	void setValue(double x)
	{
		_height = x;
		return;
	}
	void setValue(string s)
	{
		setValue(stof(s));
		return;
	}
};

class CircleRadius :public Base
{
public:
	double r;
	CircleRadius() :r(0) {}
	double getDouble()
	{
		return r;
	}
	string getType()
	{
		return "r";
	}
	void setValue(double x)
	{
		r = x;
		return;
	}
	void setValue(string s)
	{
		setValue(stof(s));
		return;
	}
};

class EllipseWidth :public Base
{
public:
	double rx;
	EllipseWidth() :rx(0) {}
	double getDouble()
	{
		return rx;
	}
	string getType()
	{
		return "rx";
	}
	void setValue(double x)
	{
		rx = x;
		return;
	}
	void setValue(string s)
	{
		setValue(stof(s));
		return;
	}
};

class EllipseHeight :public Base
{
public:
	double ry;
	EllipseHeight() :ry(0) {}
	double getDouble()
	{
		return ry;
	}
	string getType()
	{
		return "ry";
	}
	void setValue(double x)
	{
		ry = x;
		return;
	}
	void setValue(string s)
	{
		setValue(stof(s));
		return;
	}
};

class VectorPointF :public Base
{
public:
	vector<PointF> points;
	VectorPointF(){}
	void setValue(string s)
	{
		//print to file:
		ofstream out;
		out.open("inputpoint.txt");
		out << s;
		out.close();
		//input from file through formatter:
		freopen("inputpoint.txt", "r", stdin);
		float inputa, inputb;
		while (scanf("%f,%f", &inputa, &inputb) != -1)
		{
			PointF nwpoint(inputa, inputb);
			points.push_back(nwpoint);
		}
		fclose(stdin);
	}
	string getType()
	{
		return "points";
	}
	vector<PointF>& getVector()
	{
		return points;
	}
	int getSize()
	{
		return points.size();
	}
};

class _Text :public Base
{
public:
	string text;
	_Text():text(""){}
	string getType()
	{
		return "text";
	}
	string getString()
	{
		return text;
	}
	void setValue(string s)
	{
		text = s;
	}
};

class Font_size :public Base
{
public:
	double _font_size;
	Font_size() :_font_size(0) {}
	double getDouble()
	{
		return _font_size;
	}
	string getType()
	{
		return "font-size";
	}
	void setValue(double x)
	{
		_font_size = x;
		return;
	}
	void setValue(string s)
	{
		setValue(stof(s));
		return;
	}
};

class dd :public Base {
public:
	string dval;
	dd() :dval(""){}
	string getString()
	{
		return dval;
	}
	string getType()
	{
		return "d";
	}
	void setValue(string x)
	{
		dval = x;
		return;
	}
};

class Shape
{
public:
	vector<Base*> attribute;
	virtual~Shape(){}
	virtual int getSize() = 0;
	virtual string getType() { return ""; }
	virtual void input(xml_node<>*){}
	virtual void draw(HDC){}
	virtual void draw(HDC, vector<Base*> stransform){}
};

class DuongThang:public Shape
{
public:
	DuongThang()
	{
		Base* nw;
		nw = new PointAx;	//1
		attribute.push_back(nw);
		nw = new PointAy;	//2
		attribute.push_back(nw);
		nw = new PointBx;	//3
		attribute.push_back(nw);
		nw = new PointBy;	//4
		attribute.push_back(nw);
		nw = new Stroke;	//5
		attribute.push_back(nw);
		nw = new Fill;		//6
		attribute.push_back(nw);
		nw = new StrokeOpacity;	//7
		attribute.push_back(nw);
		nw = new FillOpacity;	//8
		attribute.push_back(nw);
		nw = new StrokeWidth;	//9
		attribute.push_back(nw);
		nw = new Transform;		//10
		attribute.push_back(nw);
	}
	~DuongThang()
	{
		int l = attribute.size();
		while (l--)
		{
			delete attribute[l];
		}
		attribute.clear();
	}
	int getSize()
	{
		return attribute.size();
	}
	string getType()
	{
		return "line";
	}
	void input(xml_node<> * object_node)
	{
		int sz = getSize();
		for (xml_attribute<>*attribute_node = object_node->first_attribute(); attribute_node; attribute_node = attribute_node->next_attribute())
		{
			for (int i = 0; i < sz; i++)
			{
				if (attribute_node->name() == attribute[i]->getType())
				{
					attribute[i]->setValue(attribute_node->value());
					if (i == 7)
						attribute[5]->setValid();
					else if (i == 6)
						attribute[4]->setValid();
					break;
				}
			}
		}
	}
	void draw(HDC hdc)
	{
		Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		Color color((int)(attribute[6]->getDouble() * 255), attribute[4]->getColor().GetR(), attribute[4]->getColor().GetG(), attribute[4]->getColor().GetB());
		Pen pen(color, (float)attribute[8]->getDouble());
		//transform:
		int l = (attribute[9]->getVectorTransform()).size();
		for (int i = 0; i < l; i++)
		{
			(attribute[9]->getVectorTransform())[i]->doTransform(graphics);
		}
		if(attribute[4]->getValid())graphics.DrawLine(&pen, (float)attribute[0]->getDouble(), (float)attribute[1]->getDouble(), (float)attribute[2]->getDouble(), (float)attribute[3]->getDouble());
		return;
	}
	void draw(HDC hdc, vector<Base*> stransform)
	{
		Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		int cnt = stransform.size();
		for (int i = 0; i < cnt; i++)
		{
			stransform[i]->doTransform(graphics);
		}
		Color color((int)(attribute[6]->getDouble() * 255), attribute[4]->getColor().GetR(), attribute[4]->getColor().GetG(), attribute[4]->getColor().GetB());
		Pen pen(color, (float)attribute[8]->getDouble());
		//transform:
		int l = (attribute[9]->getVectorTransform()).size();
		for (int i = 0; i < l; i++)
		{
			(attribute[9]->getVectorTransform())[i]->doTransform(graphics);
		}
		if (attribute[4]->getValid())graphics.DrawLine(&pen, (float)attribute[0]->getDouble(), (float)attribute[1]->getDouble(), (float)attribute[2]->getDouble(), (float)attribute[3]->getDouble());
		return;
	}
};

class DuongGapKhuc:public Shape
{
public:
	DuongGapKhuc()
	{
		Base* nw = new VectorPointF;	//1
		attribute.push_back(nw);
		nw = new Stroke;	//2
		attribute.push_back(nw);
		nw = new Fill;		//3
		attribute.push_back(nw);
		nw = new StrokeOpacity;	//4
		attribute.push_back(nw);
		nw = new FillOpacity;	//5
		attribute.push_back(nw);
		nw = new StrokeWidth;	//6
		attribute.push_back(nw);
		nw = new Transform;		//7
		attribute.push_back(nw);
	}
	~DuongGapKhuc()
	{
		int l = attribute.size();
		while (l--)
		{
			delete attribute[l];
		}
		attribute.clear();
	}
	string getType()
	{
		return "polyline";
	}
	int getSize()
	{
		return attribute.size();
	}
	void input(xml_node<> * object_node)
	{
		int sz = getSize();
		for (xml_attribute<>*attribute_node = object_node->first_attribute(); attribute_node; attribute_node = attribute_node->next_attribute())
		{
			for (int i = 0; i < sz; i++)
			{
				if (attribute_node->name() == attribute[i]->getType())
				{
					attribute[i]->setValue(attribute_node->value());
					if (i == 4)
						attribute[2]->setValid();
					else if (i == 3)
						attribute[1]->setValid();
					break;
				}
			}
		}
		return;
	}
	void draw(HDC hdc)
	{
		Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		Color color((int)floor(attribute[3]->getDouble() * 255), attribute[1]->getColor().GetR(), attribute[1]->getColor().GetG(), attribute[1]->getColor().GetB());
		Pen pen(color, (float)attribute[5]->getDouble());
		int l = (attribute[6]->getVectorTransform()).size();
		for (int i = 0; i < l; i++)
		{
			(attribute[6]->getVectorTransform())[i]->doTransform(graphics);
		}
		SolidBrush brush(Color((int)floor(attribute[4]->getDouble() * 255), attribute[2]->getColor().GetR(), attribute[2]->getColor().GetG(), attribute[2]->getColor().GetB()));
		if (attribute[2]->getValid())graphics.FillPolygon(&brush, &(attribute[0]->getVector())[0], attribute[0]->getSize());
		if (attribute[1]->getValid())graphics.DrawLines(&pen, &(attribute[0]->getVector())[0],attribute[0]->getSize());
		return;
	}
	void draw(HDC hdc, vector<Base*> stransform)
	{
		Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		int cnt = stransform.size();
		for (int i = 0; i < cnt; i++)
		{
			stransform[i]->doTransform(graphics);
		}
		Color color((int)floor(attribute[3]->getDouble() * 255), attribute[1]->getColor().GetR(), attribute[1]->getColor().GetG(), attribute[1]->getColor().GetB());
		Pen pen(color, (float)attribute[5]->getDouble());
		int l = (attribute[6]->getVectorTransform()).size();
		for (int i = 0; i < l; i++)
		{
			(attribute[6]->getVectorTransform())[i]->doTransform(graphics);
		}
		SolidBrush brush(Color((int)floor(attribute[4]->getDouble() * 255), attribute[2]->getColor().GetR(), attribute[2]->getColor().GetG(), attribute[2]->getColor().GetB()));
		if (attribute[2]->getValid())graphics.FillPolygon(&brush, &(attribute[0]->getVector())[0], attribute[0]->getSize());
		if (attribute[1]->getValid())graphics.DrawLines(&pen, &(attribute[0]->getVector())[0], attribute[0]->getSize());
		return;
	}
};

class DaGiac:public Shape
{
public:
	DaGiac()
	{
		Base* nw = new VectorPointF;	//1
		attribute.push_back(nw);
		nw = new Stroke;	//2
		attribute.push_back(nw);
		nw = new Fill;		//3
		attribute.push_back(nw);
		nw = new StrokeOpacity;	//4
		attribute.push_back(nw);
		nw = new FillOpacity;	//5
		attribute.push_back(nw);
		nw = new StrokeWidth;	//6
		attribute.push_back(nw);
		nw = new Transform;		//7
		attribute.push_back(nw);
	}
	~DaGiac()
	{
		int l = attribute.size();
		while (l--)
		{
			delete attribute[l];
		}
		attribute.clear();
	}
	int getSize()
	{
		return attribute.size();
	}
	void input(xml_node<> * object_node)
	{
		int sz = getSize();
		for (xml_attribute<>*attribute_node = object_node->first_attribute(); attribute_node; attribute_node = attribute_node->next_attribute())
		{
			for (int i = 0; i < sz; i++)
			{
				if (attribute_node->name() == attribute[i]->getType())
				{
					attribute[i]->setValue(attribute_node->value());
					if (i == 4)
						attribute[2]->setValid();
					else if (i == 3)
						attribute[1]->setValid();
					break;
				}
			}
		}
	}
	void draw(HDC hdc)
	{
		Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		Color color((int)(attribute[3]->getDouble() * 255), attribute[1]->getColor().GetR(), attribute[1]->getColor().GetG(), attribute[1]->getColor().GetB());
		Pen pen(color, (float)attribute[5]->getDouble());
		int l = (attribute[6]->getVectorTransform()).size();
		for (int i = 0; i < l; i++)
		{
			(attribute[6]->getVectorTransform())[i]->doTransform(graphics);
		}
		SolidBrush brush(Color((int)(attribute[4]->getDouble() * 255), attribute[2]->getColor().GetR(), attribute[2]->getColor().GetG(), attribute[2]->getColor().GetB()));
		if (attribute[2]->getValid())graphics.FillPolygon(&brush, &(attribute[0]->getVector())[0], attribute[0]->getSize());
		if (attribute[1]->getValid())graphics.DrawPolygon(&pen, &(attribute[0]->getVector())[0], attribute[0]->getSize());
		return;
	}
	void draw(HDC hdc, vector<Base*> stransform)
	{
		Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		int cnt = stransform.size();
		for (int i = 0; i < cnt; i++)
		{
			stransform[i]->doTransform(graphics);
		}
		Color color((int)(attribute[3]->getDouble() * 255), attribute[1]->getColor().GetR(), attribute[1]->getColor().GetG(), attribute[1]->getColor().GetB());
		Pen pen(color, (float)attribute[5]->getDouble());
		int l = (attribute[6]->getVectorTransform()).size();
		for (int i = 0; i < l; i++)
		{
			(attribute[6]->getVectorTransform())[i]->doTransform(graphics);
		}
		SolidBrush brush(Color((int)(attribute[4]->getDouble() * 255), attribute[2]->getColor().GetR(), attribute[2]->getColor().GetG(), attribute[2]->getColor().GetB()));
		if (attribute[2]->getValid())graphics.FillPolygon(&brush, &(attribute[0]->getVector())[0], attribute[0]->getSize());
		if (attribute[1]->getValid())graphics.DrawPolygon(&pen, &(attribute[0]->getVector())[0], attribute[0]->getSize());
		return;
	}
};

class HinhChuNhat :public Shape
{
public:
	HinhChuNhat()
	{
		Base* nw;
		nw = new PointX;	//1
		attribute.push_back(nw);
		nw = new PointY;	//2
		attribute.push_back(nw);
		nw = new Width;		//3
		attribute.push_back(nw);
		nw = new Height;	//4
		attribute.push_back(nw);
		nw = new Stroke;	//5
		attribute.push_back(nw);
		nw = new Fill;		//6
		attribute.push_back(nw);
		nw = new StrokeOpacity;	//7
		attribute.push_back(nw);
		nw = new FillOpacity;	//8
		attribute.push_back(nw);
		nw = new StrokeWidth;	//9
		attribute.push_back(nw);
		nw = new Transform;		//10
		attribute.push_back(nw);
	}
	~HinhChuNhat()
	{
		int l = attribute.size();
		while (l--)
		{
			delete attribute[l];
		}
		attribute.clear();
	}
	int getSize()
	{
		return attribute.size();
	}
	string getType()
	{
		return "rect";
	}
	void input(xml_node<> * object_node)
	{
		int sz = getSize();
		for (xml_attribute<>*attribute_node = object_node->first_attribute(); attribute_node; attribute_node = attribute_node->next_attribute())
		{
			for (int i = 0; i < sz; i++)
			{
				if (attribute_node->name() == attribute[i]->getType())
				{
					attribute[i]->setValue(attribute_node->value());
					if (i == 5 || i == 7)
						attribute[5]->setValid();
					else if (i == 4 || i == 6)
						attribute[4]->setValid();
					break;
				}
			}
		}
	}
	void draw(HDC hdc)
	{
		Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		Color color((int)(attribute[6]->getDouble() * 255), attribute[4]->getColor().GetR(), attribute[4]->getColor().GetG(), attribute[4]->getColor().GetB());
		Pen pen(color, (float)attribute[8]->getDouble());
		RectF thisrect(attribute[0]->getDouble(), attribute[1]->getDouble(), attribute[2]->getDouble(), attribute[3]->getDouble());
		SolidBrush brush(Color((int)(attribute[7]->getDouble() * 255), attribute[5]->getColor().GetR(), attribute[5]->getColor().GetG(), attribute[5]->getColor().GetB()));
		//Transform here
		int l = (attribute[9]->getVectorTransform()).size();
		for (int i = 0; i < l; i++)
		{
			(attribute[9]->getVectorTransform())[i]->doTransform(graphics);
		}
		//Draw
		if (attribute[5]->getValid())graphics.FillRectangle(&brush, thisrect);
		if (attribute[4]->getValid())graphics.DrawRectangle(&pen, thisrect);
		return;
	}
	void draw(HDC hdc, vector<Base*> stransform)
	{
		Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		int cnt = stransform.size();
		for (int i = 0; i < cnt; i++)
		{
			stransform[i]->doTransform(graphics);
		}
		Color color((int)(attribute[6]->getDouble() * 255), attribute[4]->getColor().GetR(), attribute[4]->getColor().GetG(), attribute[4]->getColor().GetB());
		Pen pen(color, (float)attribute[8]->getDouble());
		RectF thisrect(attribute[0]->getDouble(), attribute[1]->getDouble(), attribute[2]->getDouble(), attribute[3]->getDouble());
		SolidBrush brush(Color((int)(attribute[7]->getDouble() * 255), attribute[5]->getColor().GetR(), attribute[5]->getColor().GetG(), attribute[5]->getColor().GetB()));
		//Transform here
		int l = (attribute[9]->getVectorTransform()).size();
		for (int i = 0; i < l; i++)
		{
			(attribute[9]->getVectorTransform())[i]->doTransform(graphics);
		}
		//Draw
		if (attribute[5]->getValid())graphics.FillRectangle(&brush, thisrect);
		if (attribute[4]->getValid())graphics.DrawRectangle(&pen, thisrect);
		return;
	}
};

class Elip:public Shape
{
public:
	Elip()
	{
		Base* nw;
		nw = new CenterX;	//1
		attribute.push_back(nw);
		nw = new CenterY;	//2
		attribute.push_back(nw);
		nw = new EllipseWidth;	//3
		attribute.push_back(nw);
		nw = new EllipseHeight;	//4
		attribute.push_back(nw);
		nw = new Stroke;		//5
		attribute.push_back(nw);
		nw = new Fill;			//6
		attribute.push_back(nw);
		nw = new StrokeOpacity;	//7
		attribute.push_back(nw);
		nw = new FillOpacity;	//8
		attribute.push_back(nw);
		nw = new StrokeWidth;	//9
		attribute.push_back(nw);
		nw = new Transform;		//10
		attribute.push_back(nw);
	}
	~Elip()
	{
		int l = attribute.size();
		while (l--)
		{
			delete attribute[l];
		}
		attribute.clear();
	}
	int getSize()
	{
		return attribute.size();
	}
	string getType()
	{
		return "ellipse";
	}
	void input(xml_node<> * object_node)
	{
		int sz = getSize();
		for (xml_attribute<>*attribute_node = object_node->first_attribute(); attribute_node; attribute_node = attribute_node->next_attribute())
		{
			for (int i = 0; i < sz; i++)
			{
				if (attribute_node->name() == attribute[i]->getType())
				{
					attribute[i]->setValue(attribute_node->value());
					if (i == 5 || i == 7)
						attribute[5]->setValid();
					else if (i == 4 || i == 6)
						attribute[4]->setValid();
					break;
				}
			}
		}
		return;
	}
	void draw(HDC hdc)
	{
		Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		Color color((int)(attribute[6]->getDouble() * 255), attribute[4]->getColor().GetR(), attribute[4]->getColor().GetG(), attribute[4]->getColor().GetB());
		Pen pen(color, (float)attribute[8]->getDouble());
		int l = (attribute[9]->getVectorTransform()).size();
		for (int i = 0; i < l; i++)
		{
			(attribute[9]->getVectorTransform())[i]->doTransform(graphics);
		}
		SolidBrush brush(Color((int)(attribute[7]->getDouble() * 255), attribute[5]->getColor().GetR(), attribute[5]->getColor().GetG(), attribute[5]->getColor().GetB()));
		if (attribute[5]->getValid())graphics.FillEllipse(&brush, (float)(attribute[0]->getDouble() - (attribute[2]->getDouble())), (float)(attribute[1]->getDouble() - (attribute[3]->getDouble())), (float)attribute[2]->getDouble()*2, (float)attribute[3]->getDouble()*2);
		if (attribute[4]->getValid())graphics.DrawEllipse(&pen, (float)(attribute[0]->getDouble() - (attribute[2]->getDouble())), (float)(attribute[1]->getDouble() - (attribute[3]->getDouble())), (float)attribute[2]->getDouble()*2, (float)attribute[3]->getDouble()*2);
		return;
	}
	void draw(HDC hdc, vector<Base*> stransform)
	{
		Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		int cnt = stransform.size();
		for (int i = 0; i < cnt; i++)
		{
			stransform[i]->doTransform(graphics);
		}
		Color color((int)(attribute[6]->getDouble() * 255), attribute[4]->getColor().GetR(), attribute[4]->getColor().GetG(), attribute[4]->getColor().GetB());
		Pen pen(color, (float)attribute[8]->getDouble());
		int l = (attribute[9]->getVectorTransform()).size();
		for (int i = 0; i < l; i++)
		{
			(attribute[9]->getVectorTransform())[i]->doTransform(graphics);
		}
		SolidBrush brush(Color((int)(attribute[7]->getDouble() * 255), attribute[5]->getColor().GetR(), attribute[5]->getColor().GetG(), attribute[5]->getColor().GetB()));
		if (attribute[5]->getValid())graphics.FillEllipse(&brush, (float)(attribute[0]->getDouble() - (attribute[2]->getDouble())), (float)(attribute[1]->getDouble() - (attribute[3]->getDouble())), (float)attribute[2]->getDouble() * 2, (float)attribute[3]->getDouble() * 2);
		if (attribute[4]->getValid())graphics.DrawEllipse(&pen, (float)(attribute[0]->getDouble() - (attribute[2]->getDouble())), (float)(attribute[1]->getDouble() - (attribute[3]->getDouble())), (float)attribute[2]->getDouble() * 2, (float)attribute[3]->getDouble() * 2);
		return;
	}
};

class HinhTron :public Shape
{
public:
	HinhTron()
	{
		Base* nw;
		nw = new CenterX;		//1
		attribute.push_back(nw);
		nw = new CenterY;		//2
		attribute.push_back(nw);
		nw = new CircleRadius;	//3
		attribute.push_back(nw);
		nw = new Stroke;		//4
		attribute.push_back(nw);
		nw = new Fill;			//5
		attribute.push_back(nw);
		nw = new StrokeOpacity;	//6
		attribute.push_back(nw);
		nw = new FillOpacity;	//7
		attribute.push_back(nw);
		nw = new StrokeWidth;	//8
		attribute.push_back(nw);
		nw = new Transform;		//9
		attribute.push_back(nw);
	}
	~HinhTron()
	{
		int l = attribute.size();
		while (l--)
		{
			delete attribute[l];
		}
		attribute.clear();
	}
	int getSize()
	{
		return attribute.size();
	}
	string getType()
	{
		return "circle";
	}
	void input(xml_node<> * object_node)
	{
		int sz = getSize();
		for (xml_attribute<>*attribute_node = object_node->first_attribute(); attribute_node; attribute_node = attribute_node->next_attribute())
		{
			for (int i = 0; i < sz; i++)
			{
				if (attribute_node->name() == attribute[i]->getType())
				{
					attribute[i]->setValue(attribute_node->value());
					if (i == 6)
						attribute[4]->setValid();
					else if (i == 5)
						attribute[3]->setValid();
					break;
				}
			}
		}
	}
	void draw(HDC hdc)
	{
		Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		Color color((int)(attribute[5]->getDouble() * 255), attribute[3]->getColor().GetR(), attribute[3]->getColor().GetG(), attribute[3]->getColor().GetB());
		Pen pen(color, (float)attribute[7]->getDouble());
		int l = (attribute[8]->getVectorTransform()).size();
		for (int i = 0; i < l; i++)
		{
			(attribute[8]->getVectorTransform())[i]->doTransform(graphics);
		}
		SolidBrush brush(Color((int)(attribute[6]->getDouble() * 255), attribute[4]->getColor().GetR(), attribute[4]->getColor().GetG(), attribute[4]->getColor().GetB()));
		if (attribute[4]->getValid())graphics.FillEllipse(&brush, (float)(attribute[0]->getDouble() - attribute[2]->getDouble()), (float)(attribute[1]->getDouble() - attribute[2]->getDouble()), (float)(attribute[2]->getDouble() * 2), (float)(attribute[2]->getDouble() * 2));
		if (attribute[3]->getValid())graphics.DrawEllipse(&pen, (float)(attribute[0]->getDouble() - attribute[2]->getDouble()), (float)(attribute[1]->getDouble() - attribute[2]->getDouble()), (float)(attribute[2]->getDouble() * 2), (float)(attribute[2]->getDouble() * 2));
		return;
	}
	void draw(HDC hdc, vector<Base*> stransform)
	{
		Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		int cnt = stransform.size();
		for (int i = 0; i < cnt; i++)
		{
			stransform[i]->doTransform(graphics);
		}
		Color color((int)(attribute[5]->getDouble() * 255), attribute[3]->getColor().GetR(), attribute[3]->getColor().GetG(), attribute[3]->getColor().GetB());
		Pen pen(color, (float)attribute[7]->getDouble());
		int l = (attribute[8]->getVectorTransform()).size();
		for (int i = 0; i < l; i++)
		{
			(attribute[8]->getVectorTransform())[i]->doTransform(graphics);
		}
		SolidBrush brush(Color((int)(attribute[6]->getDouble() * 255), attribute[4]->getColor().GetR(), attribute[4]->getColor().GetG(), attribute[4]->getColor().GetB()));
		if (attribute[4]->getValid())graphics.FillEllipse(&brush, (float)(attribute[0]->getDouble() - attribute[2]->getDouble()), (float)(attribute[1]->getDouble() - attribute[2]->getDouble()), (float)(attribute[2]->getDouble() * 2), (float)(attribute[2]->getDouble() * 2));
		if (attribute[3]->getValid())graphics.DrawEllipse(&pen, (float)(attribute[0]->getDouble() - attribute[2]->getDouble()), (float)(attribute[1]->getDouble() - attribute[2]->getDouble()), (float)(attribute[2]->getDouble() * 2), (float)(attribute[2]->getDouble() * 2));
		return;
	}
};

class Text :public Shape
{
public:
	Text()
	{
		Base* nw = new _Text;	//1
		attribute.push_back(nw);
		nw = new Stroke;	//2
		attribute.push_back(nw);
		nw = new Fill;		//3
		attribute.push_back(nw);
		nw = new StrokeOpacity;	//4
		attribute.push_back(nw);
		nw = new FillOpacity;	//5
		attribute.push_back(nw);
		nw = new StrokeWidth;	//6
		attribute.push_back(nw);
		nw = new Transform;		//7
		attribute.push_back(nw);
		nw = new Font_size;		//8
		attribute.push_back(nw);
		nw = new PointX;		//9
		attribute.push_back(nw);
		nw = new PointY;		//10
		attribute.push_back(nw);
	}
	~Text()
	{
		int l = attribute.size();
		while (l--)
		{
			delete attribute[l];
		}
		attribute.clear();
	}
	string getType()
	{
		return "text";
	}
	int getSize()
	{
		return attribute.size();
	}
	void input(xml_node<> * object_node){
		int sz = getSize();
		for (xml_attribute<>*attribute_node = object_node->first_attribute(); attribute_node; attribute_node = attribute_node->next_attribute())
		{
			for (int i = 0; i < sz; i++)
			{
				if (attribute_node->name() == attribute[i]->getType())
				{
					attribute[i]->setValue(attribute_node->value());
					if (i == 4||i==2)
						attribute[2]->setValid();
					else if (i == 3||i==1)
						attribute[1]->setValid();
					break;
				}
			}
		}
		attribute[0]->setValue(object_node->value());
		return;
	}
	void draw(HDC hdc)
	{
		Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		FontFamily  fontFamily(L"Times New Roman");
		Font        font(&fontFamily, (int)attribute[7]->getDouble(), FontStyleRegular, UnitPixel);
		PointF      pointF((float)attribute[8]->getDouble(), (float)attribute[9]->getDouble());
		SolidBrush  brush(Color((int)attribute[4]->getDouble()*255, attribute[2]->getColor().GetR(), attribute[2]->getColor().GetG(), attribute[2]->getColor().GetB()));
		StringFormat strformat;
		string thistext = attribute[0]->getString();
		wstring wide_string = wstring(thistext.begin(), thistext.end());
		const wchar_t* pszbuf = wide_string.c_str();
		GraphicsPath path;
		path.AddString(pszbuf, wcslen(pszbuf), &fontFamily,
			FontStyleRegular, (int)attribute[7]->getDouble(), PointF((float)attribute[8]->getDouble(), (float)(attribute[9]->getDouble()-attribute[7]->getDouble())), &strformat);
		Color color((int)(attribute[3]->getDouble() * 255), attribute[1]->getColor().GetR(), attribute[1]->getColor().GetG(), attribute[1]->getColor().GetB());
		Pen pen(color, (float)attribute[5]->getDouble());

		int l = (attribute[6]->getVectorTransform()).size();
		for (int i = 0; i < l; i++)
		{
			(attribute[6]->getVectorTransform())[i]->doTransform(graphics);
		}
		if(attribute[2]->getValid())graphics.FillPath(&brush, &path);
		if(attribute[1]->getValid())graphics.DrawPath(&pen, &path);
	}
	void draw(HDC hdc, vector<Base*> stransform)
	{
		Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		int cnt = stransform.size();
		for (int i = 0; i < cnt; i++)
		{
			stransform[i]->doTransform(graphics);
		}
		FontFamily  fontFamily(L"Times New Roman");
		Font        font(&fontFamily, (int)attribute[7]->getDouble(), FontStyleRegular, UnitPixel);
		PointF      pointF((float)attribute[8]->getDouble(), (float)attribute[9]->getDouble());
		SolidBrush  brush(Color((int)attribute[4]->getDouble() * 255, attribute[2]->getColor().GetR(), attribute[2]->getColor().GetG(), attribute[2]->getColor().GetB()));
		StringFormat strformat;
		string thistext = attribute[0]->getString();
		wstring wide_string = wstring(thistext.begin(), thistext.end());
		const wchar_t* pszbuf = wide_string.c_str();
		GraphicsPath path;
		path.AddString(pszbuf, wcslen(pszbuf), &fontFamily,
			FontStyleRegular, (int)attribute[7]->getDouble(), PointF((float)attribute[8]->getDouble(), (float)(attribute[9]->getDouble() - attribute[7]->getDouble())), &strformat);
		Color color((int)(attribute[3]->getDouble() * 255), attribute[1]->getColor().GetR(), attribute[1]->getColor().GetG(), attribute[1]->getColor().GetB());
		Pen pen(color, (float)attribute[5]->getDouble());

		int l = (attribute[6]->getVectorTransform()).size();
		for (int i = 0; i < l; i++)
		{
			(attribute[6]->getVectorTransform())[i]->doTransform(graphics);
		}
		if(attribute[2]->getValid())graphics.FillPath(&brush, &path);
		if(attribute[1]->getValid())graphics.DrawPath(&pen, &path);
	}
};

class Path : public Shape {
public:
	Path()
	{
		Base* nw;
		nw = new dd;		//1
		attribute.push_back(nw);
		nw = new Stroke;    //2
		attribute.push_back(nw);
		nw = new Fill;        //3
		attribute.push_back(nw);
		nw = new StrokeOpacity;    //4
		attribute.push_back(nw);
		nw = new FillOpacity;    //5
		attribute.push_back(nw);
		nw = new StrokeWidth;    //6
		attribute.push_back(nw);
		nw = new Transform;        //7
		attribute.push_back(nw);
	}
	~Path()
	{
		int l = attribute.size();
		while (l--)
		{
			delete attribute[l];
		}
		attribute.clear();
	}
	int getSize()
	{
		return attribute.size();
	}
	string getType()
	{
		return "path";
	}
	void input(xml_node<> * object_node)
	{
		attribute[2]->setValid();
		int sz = getSize();
		for (xml_attribute<>*attribute_node = object_node->first_attribute(); attribute_node; attribute_node = attribute_node->next_attribute())
		{
			for (int i = 0; i < sz; i++)
			{
				if (attribute_node->name() == attribute[i]->getType())
				{
					attribute[i]->setValue(attribute_node->value());
					if (i == 4)
						attribute[2]->setValid();
					else if (i == 3)
						attribute[1]->setValid();
					break;
				}
			}
		}
		return;
	}
	void draw(HDC hdc)
	{
		Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		Color color((int)(attribute[3]->getDouble() * 255), attribute[1]->getColor().GetR(), attribute[1]->getColor().GetG(), attribute[1]->getColor().GetB());
		Pen pen(color, (float)attribute[5]->getDouble());
		int l = (attribute[6]->getVectorTransform()).size();
		for (int i = 0; i < l; i++)
		{
			(attribute[6]->getVectorTransform())[i]->doTransform(graphics);
		}
		SolidBrush brush(Color((int)(attribute[4]->getDouble() * 255), attribute[2]->getColor().GetR(), attribute[2]->getColor().GetG(), attribute[2]->getColor().GetB()));
		GraphicsPath path(FillModeWinding);
			PointF firstPoint;
			PointF currentPoint;
			PointF point1, point2, point3;
			PointF point;
			vector<string> res;
			string data = attribute[0]->getString();
			stringstream st;
			size_t i = 0;
			while (i < data.length())
			{
				if (data[i] == ',' || data[i] == ' ')
				{
					size_t j = i + 1;
					while (data[j] == ' ')
						data.erase(j, 1);
				}
				i++;
			}
			for (i = 0; i < data.size(); i++)
			{
				if (data[i] == ',')
					data[i] = ' ';
			}
			i = 0;
			while (i < data.size())
			{
				if ((data[i] == 'C' || data[i] == 'M' || data[i] == 'Z' || data[i] == 'H' || data[i] == 'V') && (i + 1 < data.size() && data[i + 1] != ' '))
					data.insert(i + 1, " ");
				i++;
			}
			st << data;
			while (!st.eof())
			{
				string token;
				st >> token;
				res.push_back(token);
			}
			i = 0;
			while (i < res.size())
			{
				if (res[i] == "M")
				{
					firstPoint.X = stof(res[++i]);
					firstPoint.Y = stof(res[++i]);
					currentPoint = firstPoint;
					path.Reset();
					path.SetFillMode(FillModeWinding);
				}
				else if (res[i] == "C")
				{
					point1.X = stof(res[++i]);
					point1.Y = stof(res[++i]);
					point2.X = stof(res[++i]);
					point2.Y = stof(res[++i]);
					point3.X = stof(res[++i]);
					point3.Y = stof(res[++i]);
					if (attribute[2]->getValid())
					{
						path.AddBezier(currentPoint, point1, point2, point3);
						path.CloseFigure();
						graphics.FillPath(&brush, &path);
					}
					currentPoint = point3;
				}
				else if (res[i] == "Z")
				{
					if (attribute[2]->getValid())
					{
						path.AddLine(currentPoint, firstPoint);
						graphics.FillPath(&brush, &path);
					}
					currentPoint = firstPoint;
				}
				else if (res[i] == "H")
				{
					point = currentPoint;
					point.X = stof(res[++i]);
					if (attribute[2]->getValid())
					{
						path.AddLine(currentPoint, point);
						graphics.FillPath(&brush, &path);
					}
					currentPoint = point;
				}
				else if (res[i] == "V")
				{
					point = currentPoint;
					point.Y = stof(res[++i]);
					if (attribute[2]->getValid())
					{
						path.AddLine(currentPoint, point);
						graphics.FillPath(&brush, &path);
					}
					currentPoint = point;
				}
				i++;
			
		}
			i = 0;
			while (i < res.size())
			{
				if (res[i] == "M")
				{
					firstPoint.X = stof(res[++i]);
					firstPoint.Y = stof(res[++i]);
					currentPoint = firstPoint;
					path.Reset();
					path.SetFillMode(FillModeWinding);
				}
				else if (res[i] == "C")
				{
					point1.X = stof(res[++i]);
					point1.Y = stof(res[++i]);
					point2.X = stof(res[++i]);
					point2.Y = stof(res[++i]);
					point3.X = stof(res[++i]);
					point3.Y = stof(res[++i]);
					if (attribute[1]->getValid())
						graphics.DrawBezier(&pen, currentPoint, point1, point2, point3);
					currentPoint = point3;
				}
				else if (res[i] == "Z")
				{
					if (attribute[1]->getValid())
						graphics.DrawLine(&pen, currentPoint, firstPoint);
					currentPoint = firstPoint;
				}
				else if (res[i] == "H")
				{
					point = currentPoint;
					point.X = stof(res[++i]);
					if (attribute[1]->getValid())
						graphics.DrawLine(&pen, currentPoint, point);
					currentPoint = point;
				}
				else if (res[i] == "V")
				{
					point = currentPoint;
					point.Y = stof(res[++i]);
					if (attribute[1]->getValid())
						graphics.DrawLine(&pen, currentPoint, point);
					currentPoint = point;
				}
				i++;
			}
		return;
	}
	void draw(HDC hdc, vector<Base*> stransform)
	{
		Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		Color color((int)(attribute[3]->getDouble() * 255), attribute[1]->getColor().GetR(), attribute[1]->getColor().GetG(), attribute[1]->getColor().GetB());
		Pen pen(color, (float)attribute[5]->getDouble());
		int cnt = stransform.size();
		for (int i = 0; i < cnt; i++)
		{
			stransform[i]->doTransform(graphics);
		}
		int l = (attribute[6]->getVectorTransform()).size();
		for (int i = 0; i < l; i++)
		{
			(attribute[6]->getVectorTransform())[i]->doTransform(graphics);
		}
		SolidBrush brush(Color((int)(attribute[4]->getDouble() * 255), attribute[2]->getColor().GetR(), attribute[2]->getColor().GetG(), attribute[2]->getColor().GetB()));
		GraphicsPath path(FillModeWinding);
		PointF firstPoint;
		PointF currentPoint;
		PointF point1, point2, point3;
		PointF point;
		vector<string> res;
		string data = attribute[0]->getString();
		stringstream st;
		size_t i = 0;
		while (i < data.length())
		{
			if (data[i] == ',' || data[i] == ' ')
			{
				size_t j = i + 1;
				while (data[j] == ' ')
					data.erase(j, 1);
			}
			i++;
		}
		for (i = 0; i < data.size(); i++)
		{
			if (data[i] == ',')
				data[i] = ' ';
		}
		i = 0;
		while (i < data.size())
		{
			if ((data[i] == 'C' || data[i] == 'M' || data[i] == 'Z' || data[i] == 'H' || data[i] == 'V') && (i + 1 < data.size() && data[i + 1] != ' '))
				data.insert(i + 1, " ");
			i++;
		}
		st << data;
		while (!st.eof())
		{
			string token;
			st >> token;
			res.push_back(token);
		}
		i = 0;
		while (i < res.size())
		{
			if (res[i] == "M")
			{
				firstPoint.X = stof(res[++i]);
				firstPoint.Y = stof(res[++i]);
				currentPoint = firstPoint;
				path.Reset();
				path.SetFillMode(FillModeWinding);
			}
			else if (res[i] == "C")
			{
				point1.X = stof(res[++i]);
				point1.Y = stof(res[++i]);
				point2.X = stof(res[++i]);
				point2.Y = stof(res[++i]);
				point3.X = stof(res[++i]);
				point3.Y = stof(res[++i]);
				if (attribute[2]->getValid())
				{
					path.AddBezier(currentPoint, point1, point2, point3);
					path.CloseFigure();
					graphics.FillPath(&brush, &path);
				}
				currentPoint = point3;
			}
			else if (res[i] == "Z")
			{
				if (attribute[2]->getValid())
				{
					path.AddLine(currentPoint, firstPoint);
					graphics.FillPath(&brush, &path);
				}
				currentPoint = firstPoint;
			}
			else if (res[i] == "H")
			{
				point = currentPoint;
				point.X = stof(res[++i]);
				if (attribute[2]->getValid())
				{
					path.AddLine(currentPoint, point);
					graphics.FillPath(&brush, &path);
				}
				currentPoint = point;
			}
			else if (res[i] == "V")
			{
				point = currentPoint;
				point.Y = stof(res[++i]);
				if (attribute[2]->getValid())
				{
					path.AddLine(currentPoint, point);
					graphics.FillPath(&brush, &path);
				}
				currentPoint = point;
			}
			i++;

		}
		i = 0;
		while (i < res.size())
		{
			if (res[i] == "M")
			{
				firstPoint.X = stof(res[++i]);
				firstPoint.Y = stof(res[++i]);
				currentPoint = firstPoint;
				path.Reset();
				path.SetFillMode(FillModeWinding);
			}
			else if (res[i] == "C")
			{
				point1.X = stof(res[++i]);
				point1.Y = stof(res[++i]);
				point2.X = stof(res[++i]);
				point2.Y = stof(res[++i]);
				point3.X = stof(res[++i]);
				point3.Y = stof(res[++i]);
				if (attribute[1]->getValid())
					graphics.DrawBezier(&pen, currentPoint, point1, point2, point3);
				currentPoint = point3;
			}
			else if (res[i] == "Z")
			{
				if (attribute[1]->getValid())
					graphics.DrawLine(&pen, currentPoint, firstPoint);
				currentPoint = firstPoint;
			}
			else if (res[i] == "H")
			{
				point = currentPoint;
				point.X = stof(res[++i]);
				if (attribute[1]->getValid())
					graphics.DrawLine(&pen, currentPoint, point);
				currentPoint = point;
			}
			else if (res[i] == "V")
			{
				point = currentPoint;
				point.Y = stof(res[++i]);
				if (attribute[1]->getValid())
					graphics.DrawLine(&pen, currentPoint, point);
				currentPoint = point;
			}
			i++;
		}
		return;
	}
};

class Group :public Shape
{
public:
	vector<Shape*> g;
	Group()
	{
		Base* nw;
		nw = new Stroke;		//1
		attribute.push_back(nw);
		nw = new Fill;			//2
		attribute.push_back(nw);
		nw = new StrokeOpacity;	//3
		attribute.push_back(nw);
		nw = new FillOpacity;	//4
		attribute.push_back(nw);
		nw = new StrokeWidth;	//5
		attribute.push_back(nw);
		nw = new Transform;		//6
		attribute.push_back(nw);
	}
	~Group()
	{
		int l = g.size();
		while (l--)
			delete g[l];
		g.clear();
	}
	int getSize()
	{
		return attribute.size();
	}
	string getType()
	{
		return "g";
	}
	void update()
	{
		int l = g.size();
		for (int i = l-1; i < l; i++)
		{
			int k = g[i]->getSize();
			for (int j = 0; j < k; j++)
			{
				string thisatt = (g[i]->attribute)[j]->getType();
				if (thisatt == "stroke")
				{
					if(attribute[0]->getValid())
						(g[i]->attribute)[j]->setValue(attribute[0]->getColor().GetR(), attribute[0]->getColor().GetG(), attribute[0]->getColor().GetB());
				}
				else if (thisatt == "fill")
				{
					if (attribute[1]->getValid())
						(g[i]->attribute)[j]->setValue(attribute[1]->getColor().GetR(), attribute[1]->getColor().GetG(), attribute[1]->getColor().GetB());
				}
				else if (thisatt == "stroke-opacity")
				{
					(g[i]->attribute)[j]->setValue(attribute[2]->getDouble());
				}
				else if (thisatt == "fill-opacity")
				{
					(g[i]->attribute)[j]->setValue(attribute[3]->getDouble());
				}
				else if (thisatt == "stroke-width")
				{
					(g[i]->attribute)[j]->setValue((long long)attribute[4]->getDouble());
				}
			}
		}
		return;
	}
	void input(xml_node<>* object_node)
	{
		int sz = getSize();
		for (xml_attribute<>*attribute_node = object_node->first_attribute(); attribute_node; attribute_node = attribute_node->next_attribute())
		{
			for (int i = 0; i < sz; i++)
			{
				if (attribute_node->name() == attribute[i]->getType())
				{
					attribute[i]->setValue(attribute_node->value());
					if (i == 4)
						attribute[2]->setValid();
					else if (i == 3)
						attribute[1]->setValid();
					break;
				}
			}
		}
		Shape* nw_shape;
		for (xml_node<>* shape_daughter = object_node->first_node(); shape_daughter; shape_daughter=shape_daughter->next_sibling())
		{
			nw_shape = NULL;
			string stmp = shape_daughter->name();
			if (stmp == "line")
				nw_shape = new DuongThang;
			else if (stmp == "polyline")
				nw_shape = new DuongGapKhuc;
			else if (stmp == "polygon")
				nw_shape = new DaGiac;
			else if (stmp == "rect")
				nw_shape = new HinhChuNhat;
			else if (stmp == "circle")
				nw_shape = new HinhTron;
			else if (stmp == "ellipse")
				nw_shape = new Elip;
			else if (stmp == "text")
				nw_shape = new Text;
			else if (stmp == "g")
				nw_shape = new Group;
			else if (stmp == "path")
				nw_shape = new Path;
			if (nw_shape != NULL)
			{
				g.push_back(nw_shape);
				update();
				nw_shape->input(shape_daughter);
			}
		}
		return;
	}
	void draw(HDC hdc)
	{
		int l = g.size();
		for (int i = 0; i < l; i++)
		{
			g[i]->draw(hdc, attribute[5]->getVectorTransform());
		}
	}
	void draw(HDC hdc, vector<Base*> stransform)
	{
		vector<Base*> nwtransform = stransform;
		int cnt = (attribute[5]->getVectorTransform()).size();
		for (int i = 0; i < cnt; i++)
		{
			nwtransform.push_back(attribute[5]->getVectorTransform()[i]);
		}
		int l = g.size();
		for (int i = 0; i < l; i++)
		{
			g[i]->draw(hdc, nwtransform);
		}
	}
};

void inputFromFile(vector<Shape*> &__shape)
{
	//cout << "Parsing the file ......." << endl;
	xml_document<> doc;
	xml_node<> * root_node;
	ifstream theFile("sample.svg");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	root_node = doc.first_node("svg");
	for (xml_node<> * object_node = root_node->first_node(); object_node; object_node = object_node->next_sibling())
	{
		//cout << "This is object: " << object_node->name() << endl;
		Shape* nw = NULL;
		string stmp = object_node->name();
		if (stmp == "line")
			nw = new DuongThang;
		else if (stmp == "polyline")
			nw = new DuongGapKhuc;
		else if (stmp == "polygon")
			nw = new DaGiac;
		else if (stmp == "rect")
			nw = new HinhChuNhat;
		else if (stmp == "circle")
			nw = new HinhTron;
		else if (stmp == "ellipse")
			nw = new Elip;
		else if (stmp == "text")
			nw = new Text;
		else if (stmp == "g")
			nw = new Group;
		else if (stmp == "path")
			nw = new Path;
		if (nw != NULL) 
		{
			nw->input(object_node);
			__shape.push_back(nw);
		}
	}
	return;
}

void closeProject(vector<Shape*> &__shape)
{
	int l = __shape.size();
	while (l--)
		delete __shape[l];
	__shape.clear();
}