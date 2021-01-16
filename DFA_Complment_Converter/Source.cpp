#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <gl/glut.h>
using namespace std;

int initialState;
int ToState[100];
bool isFinal[100];
int FromState[100];
char transChar[100];
int showComplment=1;
int NUmberOfStates=12;
double GL_PI = 3.1415f;
int NumberOfTranstions=0;
bool isLive[100];

vector < vector < pair < int, char > > > adjList;
pair < int, int > stLoc[100];
vector < int > ans;
string path = "";

void findLiveStates(int u) {
	if (isLive[u])
		return;
	isLive[u] = 1;
	for (auto ch : adjList[u])
		if (!isLive[ch.first])
			findLiveStates(ch.first);
}

void findWay(int u , string toFind , vector < int > v) {
	
	if (v.size() == toFind.size()&&ans.size()==1&&isFinal[v[v.size()-1]]) {
		for (auto e : v)
			ans.push_back(e);
		return;
	}
	for (auto ch : adjList[u])
		if (toFind[v.size()] == ch.second&&v.size()<toFind.size()&&ans.size()==1) {
			v.push_back(ch.first);
			findWay(ch.first, toFind, v);
			v.pop_back();
		}
}

int toInt(string s) {
	int sum = 0;
	for (int i = 0; i < s.size(); i++)
		sum = (sum * 10) + (s[i] - '0');
	return sum;
}
string toString(int idx) {

	char strr[100];
	int cnt = 0;
	if (!idx) { strr[cnt] = '0'; cnt++; }
	while (idx) {
		strr[cnt] = ((idx % 10) + '0');
		cnt++;
		idx /= 10;
	}
	string ans = "";
	for (int i = 0; i < cnt; i++)
		ans += strr[i];

	reverse(ans.begin(), ans.end());
	return ans;
}

void displayText(float x, float y, string word, int FontSize , float red, float green,float blue) {
	glColor3f(red, green, blue);
	glRasterPos2f(x, y);
	for (int i = 0; i < word.size(); i++)
		if (FontSize == 1)glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, word[i]);
		else if (FontSize == 2)glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, word[i]);
		else if (FontSize == 3)glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, word[i]);
		else if (FontSize == 4)glutBitmapCharacter(GLUT_BITMAP_8_BY_13, word[i]);
		else if (FontSize == 5)glutBitmapCharacter(GLUT_BITMAP_9_BY_15, word[i]);
		else if (FontSize == 6)glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, word[i]);
		else if (FontSize == 7)glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, word[i]);
}

void read() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	string k,s;
	int finals;

	cin >> s >> NUmberOfStates >> s >> NumberOfTranstions >> s >> finals >> s >> showComplment;
	adjList.resize(NUmberOfStates);

	for (int i = 0; i < NUmberOfStates && (showComplment!=1); i++)
		isFinal[i] = 1;

	cin >> s >> s;
	s.erase(s.begin());
	initialState = toInt(s);
	cin >> s;
	for (int i = 0; i < finals; i++) {
		cin >> s;
		s.erase(s.begin());
		if (showComplment == 1)
			isFinal[toInt(s)] = 1;
		else 
			isFinal[toInt(s)] = 0;
	}
	cin >> s;
	for (int i = 0; i < NumberOfTranstions; i++) {
		cin >> s;
		s.erase(s.begin());
		FromState[i] = toInt(s);
		cin >> transChar[i] >> s ;
		s.erase(s.begin());
		ToState[i] = toInt(s);

		if (showComplment!=1)
			adjList[ToState[i]].push_back({ FromState[i],transChar[i] });
		else
			adjList[FromState[i]].push_back({ ToState[i],transChar[i] });
	}
	
	if (adjList[initialState].size())findLiveStates(initialState);

	if (showComplment==2)
		for (int i = 0; i < NumberOfTranstions; i++)
			swap(FromState[i], ToState[i]);

	string findThis;
	cin >> s >>  findThis;

	ans.push_back(initialState);
	findWay(initialState, findThis,vector < int > ());
	
    path = findThis;

	if (ans.size() != 1) {
		path += " belong to this DFA & path is : ";
		for (int i = 0; i < ans.size(); i++)
			if (!i) { path += "q"; path+= toString(ans[i]);}
			else { path += " => q"; path += toString(ans[i]); }
	}
	else
		path += " does not belong to this DFA";
	cout << path << endl;
}

void drawArrowPoint(double x, double y, double xx, double yy) {

	glColor3f(1, 1, 1);
		double lx = (x + xx) / 2.0;
		double ly = (y + yy) / 2.0;

		while (abs(lx - xx)*abs(lx - xx) + abs(ly - yy)*abs(ly - yy) >= 64*3) {
			lx = (lx + xx) / 2.0;
			ly = (ly + yy) / 2.0;
		}
		glPointSize(5);
		glBegin(GL_POINTS);
		glVertex2f(lx, ly);
		glEnd();
		glPointSize(2);

		displayText(-95, 95, path, 2, 1, 1, 1);
		displayText(-45, -90, "DFA Complment Converter", 7, 1, 1, 1);
}

void drawLine(int x, int y, int x2, int y2) {
	glColor3f(1, 1, 1);
	glBegin(GL_LINE_STRIP);
	glVertex2i(x, y);
	glVertex2i(x2, y2);
	glEnd();
}

void drawTransition(double x, double y , double xx , double yy , char ch) {

	if (x == xx&&y == yy) {
		int nearestX = 0, nearestY = 0;
		for (int i = -100; i <= 100; i+=10) {
			for (int k = -100; k <= 100; k+=10) {
				if (i != -100 && k != -100 && i != 100 && k != 100)continue;
				if ((x - nearestX)*(x - nearestX) + (y - nearestY)*(y - nearestY) >
					(x - i)*(x - i) + (y - k)*(y - k))
					nearestX = i, nearestY = k;
			}
		}
		drawTransition(nearestX, nearestY,x,y, ch);
		return;
	}
	if (x == 100 || x == -100 || y == 100 || y == -100) {
		x = (((x + xx) / 2));
		y = (((y + yy) / 2));
		drawLine(x, y, xx, yy);
	}
	else {
		x = (((x + xx) / 2) + xx) / 2;
		y = (((y + yy) / 2) + yy) / 2;
	}
	glColor3f(0, 1, 0);

	glBegin(GL_POLYGON);
	for (GLfloat angle = 0.0f; angle <= (2.0f*GL_PI); angle += (2.0f*GL_PI) / 20)
		glVertex2f(x + 3 * sin(angle), y + 3 * cos(angle));
	glEnd();

	glColor3f(0, 0, 0);
	glRasterPos2f(x - 1, y + 1.5);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, ch);
}

void drawCircle(double x , double y , int idx) {
	
	(!isLive[idx]||((!adjList[idx].size()||adjList[idx].size()==1&&adjList[idx][0].first==idx)&&!isFinal[idx]) 
		? glColor3f(.7, .7, .7) : isFinal[idx] 
		? glColor3f(1, 0, 0) : glColor3f(0, 0, 1));	
	
	glBegin(GL_POLYGON);
	for (GLfloat angle = 0.0f; angle <= (2.0f*GL_PI); angle += (2.0f*GL_PI) / 20)
		glVertex2f(x+ 5 * sin(angle), y+ 5 * cos(angle));
	glEnd();

	string str = idx == initialState ? "(q"+toString(idx)+")" : "q" + toString(idx);
	displayText(x - 3, y+1 , str, 3, 1, 1, 1);
}

void RenderScene(void)
{
	int i = 0;
	glColor3f(1, 0, 0);

	glBegin(GL_POINTS);
	for (GLfloat angle = 0.0f; angle <= (2.0f*GL_PI); angle+=(2.0f*GL_PI)/ NUmberOfStates){
		stLoc[i].first = 75*sin(angle);
		stLoc[i].second = 75*cos(angle);
		glVertex2f(stLoc[i].first, stLoc[i].second);
		i++;
	}
	glEnd();

	for (int i = 0; i < NumberOfTranstions; i++) 
		drawLine(stLoc[FromState[i]].first, stLoc[FromState[i]].second,
			stLoc[ToState[i]].first, stLoc[ToState[i]].second);
	
	for (int i = 0; i < NumberOfTranstions; i++) 
		drawArrowPoint(stLoc[FromState[i]].first, stLoc[FromState[i]].second,
			stLoc[ToState[i]].first, stLoc[ToState[i]].second);

	for (int i = 0; i < NumberOfTranstions; i++) 
		drawTransition(stLoc[FromState[i]].first, stLoc[FromState[i]].second,
			stLoc[ToState[i]].first, stLoc[ToState[i]].second, transChar[i]);

	for(int t = 0 ; t < NUmberOfStates ;t++)
		drawCircle(stLoc[t].first, stLoc[t].second,t);

	glutSwapBuffers();
}
void main(int argc, char* argv[]){

	read();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(620, 620);
	glutCreateWindow("Automta 1'Complment Converter");
	glutDisplayFunc(RenderScene);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glLineWidth(2);
	glPointSize(5);
	glColor3f(0.0f, 1.0f, 0.0f);
	glOrtho(-100, 100, 100, -100, -100, 100);
	glutMainLoop();
}