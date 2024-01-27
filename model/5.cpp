//#define STB_IMAGE_IMPLEMENTATION
//#define GLUT_DISABLE_ATEXIT_HACK
//#include <List>
//#include <vector>
//#include "GLUT.H"
//#include <math.h>
//#include <string.h>
//#include <map>
//#include<iostream>
//#include <fstream>
//#include <sstream>
//#include "My_3DVector.h"
//#include"stb_image.h"
//using namespace std;
//#define PI 3.1415
//#define nearplane_width 800//�Ӿ�����
//#define nearplane_height 800 //�Ӿ���߶�
//
//int nearplane_distance = 1000; //�Ӿ����ƽ�����ӵ����
//int farplane_distance = nearplane_distance + 300; //�Ӿ���Զƽ�����ӵ����
//int shadowDistance = 100;
//#define colorDepth 10
//class Color {
//public:
//	float data[4];
//	Color(float x = 0, float y = 0, float z = 0, float a = 1) {
//		data[0] = x;
//		data[1] = y;
//		data[2] = z;
//		data[3] = a;
//	}
//};
//
//float eye_x = 0, eye_y = 2500, eye_z = 1000;	//�Ӿ�����λ��
////float eye_x = 0, eye_y =0, eye_z = -500;
//float look_x = 0, look_y = 0, look_z = 1;		//����ķ���
//float pitch = 0, yaw = PI / 2;		//�Ƕ�
//int last_x = nearplane_width / 2, last_y = 0;
//
//int speed = 100;		//�Ӿ������ƶ��ٶ�
//float sensitivity = 0.002;		//�������������
//int isperspective = 1;		//�Ƿ���͸��ͶӰ
//Color color[nearplane_height][nearplane_width];
//vector<string> split(string T, string P) {
//	vector<string> arr;
//	if (T == "")return arr;
//	unsigned point1 = 0, point2 = 0;
//	if (P == "" || T.find(P, point1) == string::npos) {//���ָ����ԭ�ַ����Ҳ����ָ��
//		arr.push_back(T);
//		return arr;
//	}
//	while ((point1 = T.find(P, point1)) != string::npos) {
//		if (point1 == point2)arr.push_back("");
//		else arr.push_back(T.substr(point2, point1 - point2));
//		point2 = point1 + P.length();//����ƥ�䴮P
//		point1 += P.length();
//	}
//	if (point2 <= T.length() - 1)arr.push_back(T.substr(point2, T.length() - point2));
//	return arr;
//}
//
//int Count[800] = {0};
//void read(string url)
//{
//	ifstream file;
//
//	file.open(url, ios_base::in);
//
//	if (!file.is_open())
//	{
//		cout << "���ļ�ʧ��";
//		return;
//	}
//
//	string s;
//	while (getline(file, s))
//	{
//		vector<string>str = split(s, " ");
//		if (str.size() < 5)continue;
//		int i = atof(str[0].c_str());
//		int j = atof(str[1].c_str());
//		if (i < 0 || i>800 || j < 0 || j>800)continue;
//
//		color[i][j+ Count[i]*160].data[0]= atof(str[2].c_str());
//		color[i][j + Count[i] * 160].data[1] = atof(str[3].c_str());
//		color[i][j + Count[i] * 160].data[2] = atof(str[4].c_str());
//		Count[i] += 1;
//	}
//	file.close();
//
//}
//void init()
//{
//	/*for (int i = 0; i < 5; i++)
//	{
//		string url = "./������/1/" + to_string(i);
//		read( url + ".txt");
//		cout << i << endl;
//	}*/
//	string url = "./������/5.txt" ;
//	read(url);
//	//cout << i << endl;
//}
//
//
//void display(void) {
//
//	glBegin(GL_POINTS);
//	for (int i = 0; i < nearplane_height; i++) {
//		for (int j = 0; j < nearplane_width; j++) {
//			//Color totalColor= color[i][j];
//			glColor3f(color[i][j].data[0], color[i][j].data[1], color[i][j].data[2]);
//			glVertex2i(j - nearplane_width / 2, i - nearplane_height / 2);
//		}
//	}
//	
//	glEnd();
//	glutSwapBuffers();
//}
//
////ͶӰ��ʽ��modelview��ʽ����
//void reshape(int w, int h)
//{
//	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	if (w <= h)
//		glOrtho(-0.5 * nearplane_width, 0.5 * nearplane_width, -0.5 * nearplane_height * (GLfloat)nearplane_height / (GLfloat)nearplane_width, 0.5 * nearplane_height * (GLfloat)nearplane_height / (GLfloat)nearplane_width,
//			-nearplane_distance, nearplane_distance + 1000); //������ӵ�
//	else
//		glOrtho(-0.5 * nearplane_width, 0.5 * nearplane_width, -0.5 * nearplane_height * (GLfloat)nearplane_width / (GLfloat)nearplane_height, 0.5 * nearplane_height * (GLfloat)nearplane_width / (GLfloat)nearplane_height,
//			-nearplane_distance, nearplane_distance + 1000);
//
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//}
//
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(nearplane_width, nearplane_height);
//	glutInitWindowPosition(100, 100);
//	glutCreateWindow("zbuffer");
//	init();
//	glutReshapeFunc(reshape);
//	glutDisplayFunc(display);
//	//glutKeyboardFunc(keyboard);
//	/*glutPassiveMotionFunc(mouse);*/
//	glutMainLoop();
//	return 0;
//}