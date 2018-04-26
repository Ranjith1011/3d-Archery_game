/*3D Arrow game
Team members:E.Ranjith Kumar(1500001011),Thota Sri Ranga Vineel(1500001036)
*/



#include <GL/glut.h>				//Including the required header files
#include <bits/stdc++.h>
#define PI 3.14152653597689786
#define RandomFactor 2.0
#define ESCAPE 27
#define ENTER 13
#define FRONT 56
#define BACK 50
#define LEFT 52
#define RIGHT 54
#define TEXTID 3

using namespace std;
							//Declaring the required variables
string s;
int f=0,vflag=0,flag=0,A_left=5,scr=0,ind,t=0;
GLfloat xt=0.0,yt=0.0,zt=0.0,xangle=0.0,yangle=0.0,zangle=0.0,OuterRadius=2.4;
GLdouble x=0.1,y=0.1;
float incx=0.0,incy=0.0,incz=0.0,t1=10,t3=0;
float arr[10]={2.0,-2.0,1.0,-1.0,0.0,3.0,-3.0,4.0,-4.0,5.0};
float xarr1,yarr1,zarr1,xarr2,yarr2,zarr2,xarr,yarr,zarr,ang,x_cha=0.0,m=0.0,first=1.0,ind_ang=170.0,x_ind,y_ind,z_ind;
GLuint grass,sky;


void initialize(){			//Called each time after arrow hits the target plane to initialize the values back to initial state 
	incx=0.0;
	incy=0.0;
	incz=0.0;
	xt=0.0;
	yt=0.0;
	zt=0.0;
	flag=0;
	A_left-=1;
	first=1.0;
	t1=5;
	t3=0;
	if(A_left==0){
		f=2;
	}
}



void initGL() {					
   	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
   	glClearDepth(1.0f);                   
   	glEnable(GL_DEPTH_TEST);   
   	glDepthFunc(GL_LEQUAL);   
   	glShadeModel(GL_SMOOTH);  
   	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	gluPerspective(45,1440.0/720.0,1.0,500.0);
   	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  
}

GLuint LoadBMP(const char *fileName)					//Function to load the texture(bmp file)
{
	FILE *file;
	unsigned char header[54],*data;
	unsigned int dataPos,size,width, height;
	file = fopen(fileName, "rb");
	fread(header, 1, 54, file);				
	dataPos		= *(int*)&(header[0x0A]);	
	size		= *(int*)&(header[0x22]);	
	width		= *(int*)&(header[0x12]);	
	height		= *(int*)&(header[0x16]);	
	if (size == NULL)
		size = width * height * 3;
	if (dataPos == NULL)
		dataPos = 54;
	data = new unsigned char[size];
	fread(data, 1, size, file);
	fclose(file);
	GLuint texture;
	glGenTextures(1, &texture);				
	glBindTexture(GL_TEXTURE_2D, texture);	



	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data); 
	return texture;
}

void initTexture()					//Loading the required textures and mapping it to certain Gluint 
{
	glShadeModel(GL_SMOOTH);							
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);			
	glClearDepth(1.0f);									
	glEnable(GL_DEPTH_TEST);													
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
	sky=LoadBMP("BMP11/front.bmp");
	grass=LoadBMP("BMP11/grass_1.bmp");
	
}


void draw_circle(float rad,float r,float g,float b)		//Function to draw circles on target board
{
	int i,j;
	glPushMatrix();
	glTranslatef(x_cha,0.0,-10.0);
	glBegin(GL_POLYGON);
	glColor3f(r,g,b);	
 	for(i=0;i<1000;++i)
  	{
  		glVertex3f(rad*cos(2*3.14159*i/1000.0),rad*sin(2*3.14159*i/1000.0)+1.5,0);
  	}
 	glEnd();
	glPopMatrix();
	glFlush();
}

void draw_angle_board()			//Function to draw the angular board to fix the arrow direction
{
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
	glTranslatef(-xt,-yt,-zt);
	glBegin(GL_POLYGON);
	for(int i=0;i<=180;i++)
	{
		glVertex3f(0.5*cos(3.14159*i/180.0)+3.0,0.5*sin(3.14159*i/180.0)+3.0,0);
	}
	glEnd();
	if(flag!=1)
	{
		t+=1;
		if(ind_ang==10 && t>50){
			ind_ang=170;
			t=0;
		}
		if(ind_ang<=170 && t>50){
			ind_ang-=5;
			t=0;
		}
		glColor3f(0.5,0.0,0.0);
		glLineWidth(3.0);
		x_ind=0.4*cos(3.14159*ind_ang/180)+3;
		y_ind=0.4*sin(3.14159*ind_ang/180)+3;
		z_ind=0.0;
		glBegin(GL_LINES);
			glVertex3f(3.0,3.0,0.0);
			glVertex3f(x_ind,y_ind,z_ind);
			
		glEnd();
	}
	glPopMatrix();
}

void speed_bar(){						//Function to draw the speed-bar(by pressing 'a' to change speed
	glColor3f(1.0,0.0,0.0);
	glPushMatrix();
	glTranslatef(-xt,-yt,-zt);
	glBegin(GL_POLYGON);
		glVertex3f(1.5,1.0,0.0);
		glVertex3f(2.0,1.0,0.0);
		glVertex3f(2.0,3.0-(t1/5),0.0);
		glVertex3f(1.5,3.0-(t1/5),0.0);
	glEnd();
	glPopMatrix();
}

void Arrow()					//Function to draw Arrow and evaluate the score
{
	yarr1=1.5;
	yarr2=1.5;
	m=tan(3.14159*(180-ind_ang)/180);
	if(flag==1){
			if(first==1){
				first=0;
				xarr1=0.0;
				zarr1=0.0;
				zarr2=-0.1;
				if(m!=0.0)
					xarr2=zarr2/m;
				else
					xarr2=0.0;
			}		
			else{
				if(t3==t1){
				xarr1=xarr2;
				zarr1=zarr2;
				zarr2-=0.1;
				if(m!=0.0)
					xarr2=zarr2/m;
				else
					xarr2=0.0;
				t3=0;
				}
			}
		t3+=1;
		
	}
	else{
		xarr1=0.0;
		yarr1=1.5;
		zarr1=0.0;
		xarr2=0.0;
		yarr2=1.5;
		zarr2=-0.2;
	}
	glColor3f(0.5,0.0,0.0);
	glPushMatrix();
	glLineWidth(5.0);
	glBegin(GL_LINES);
		glVertex3f(xarr1,yarr1,zarr1);
		glVertex3f(xarr2,yarr2,zarr2);
	glEnd();
	glBegin(GL_TRIANGLES);
		glTexCoord2f(1.0,0.0);glVertex3f(xarr2-0.1,yarr2,zarr2+0.1);
		glTexCoord2f(0.0,1.0);glVertex3f(xarr2+0.1,yarr2,zarr2+0.1);
		glTexCoord2f(1.0,1.0);glVertex3f(xarr2,yarr2,zarr2);
	glEnd();
	glPopMatrix();
	
	if(zarr2<=-16){
		xarr=xarr2-x_cha;
		yarr=yarr2-1.3;
		if((xarr2)*(xarr2)+(yarr*yarr)<=0.2*0.2+0){
			scr+=50;
		}
		else if((xarr*xarr)+(yarr*yarr)<=0.25*0.25){
			scr+=40;
		}
		else if((xarr*xarr)+(yarr*yarr)<=0.35*0.35){
			scr+=30;
		}
		else if((xarr*xarr)+(yarr*yarr)<=0.5*0.5){
			scr+=20;
		}
		else if((xarr*xarr)+(yarr*yarr)<=0.7*0.7){
			scr+=10;
		}
		vflag=0;
		ind=rand()%10;
		x_cha=arr[ind];
		initialize();
	}
	
	
	
}

void NormalKey(GLubyte key, GLint x, GLint y)
{
	if(f==0)
	{
		switch ( key )
		{
			case 13:
			case '1': f=3; break;
			case '2': f=1; break;
			case '3':
			case ESCAPE: exit(0);
			glutPostRedisplay();
		}
	}
	else if(f==1)
	{
		if(key=='b'||key=='B')
			f=0;
		else
			f=3;
		glutPostRedisplay();
	}
	else if(f==2)
	{
		switch( key )
		{
			case ENTER :
				f=0;
				scr=0;
				break;
			default:
				break;
		}
	}
	else
	{
	if(key == 'a'){
		t1-=1;
		if(t1==0){
			t1=10;
		}
	}
	switch ( key )
	{			
		case ESCAPE :
			printf("Thank You\nAny Suggestions??????\n\n\n");
			exit(0);
			break;
		case ENTER :
			flag=1;
			glutPostRedisplay();
			break;
		case FRONT:
			vflag=5;
			glutPostRedisplay();
			break;
		case BACK:
			vflag=6;
			glutPostRedisplay();
			break;
		case LEFT:
			vflag=7;
			glutPostRedisplay();
			break;
		case RIGHT:
			vflag=8;
			glutPostRedisplay();
			break;
		case 'b': case 'B':
			f=0;
			glutPostRedisplay();
			break;
		case 'h': case 'H':
			f=1;
			glutPostRedisplay();
			break;
		default:
		break;
	}
	}
}

void SpecialKey(int key, int xx, int yy)
{
	if(f!=0 && f!=1){
		switch ( key )
		{
			case GLUT_KEY_UP:
				vflag=1;
				glutPostRedisplay();
				break;
			case GLUT_KEY_DOWN:
				vflag=2;
				glutPostRedisplay();
				break;
			case GLUT_KEY_LEFT:
				vflag=3;
				glutPostRedisplay();
				break;
			case GLUT_KEY_RIGHT:
				vflag=4;
				glutPostRedisplay();
				break;
			default:
			break;
		}
	}
}

void DrawTextXY(double x,double y,double z,double scale)			//Write text on the frame
{
	int i;
	glPushMatrix();
	glTranslatef(-xt+x,-yt+y,-zt+z);
	glScalef(scale,scale,scale);
	for (i=0;i < s.size();i++)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,s[i]);
	glPopMatrix();
}

void Draw_sky()						//Fix the background texture
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,sky);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0);glVertex3f(-OuterRadius*10.0,OuterRadius*10.0,-12.0);
	glTexCoord2f(1.0,0.0);glVertex3f(-OuterRadius*10.0,-OuterRadius*10.0,-12.0);
	glTexCoord2f(1.0,1.0);glVertex3f(OuterRadius*10.0,-OuterRadius*10.0,-12.0);
	glTexCoord2f(0.0,1.0);glVertex3f(OuterRadius*10.0,OuterRadius*10.0,-12.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
} 


void Draw_ground()					//Fix the ground texture
{
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,grass);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0);glVertex3f(-OuterRadius*10.0,0.0,OuterRadius*10.0);
	glTexCoord2f(1.0,0.0);glVertex3f(-OuterRadius*10.0,0.0,-OuterRadius*10.0);
	glTexCoord2f(1.0,1.0);glVertex3f(OuterRadius*10.0,0.0,-OuterRadius*10.0);
	glTexCoord2f(0.0,1.0);glVertex3f(OuterRadius*10.0,0.0,OuterRadius*10.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Score(){					//write the updated score and arrows left
	stringstream out1,out2;
	glColor3f(1.0,0.0,0.0);
	s = " Score ";
	DrawTextXY(-7,6.2,0.0,0.002);
	out1 << scr;
	s = out1.str();
	DrawTextXY(-4.0,6.2,0.0,0.002);
	glColor3f(1.0,0.0,0.0);
	s = " Arrows left ";
	DrawTextXY(-7,5.8,0.0,0.002);
	out2 << A_left;
	s = out2.str();
	DrawTextXY(-4.0,5.8,0.0,0.002);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glTranslatef(0.0,0.0,-6.0);
	glTranslatef(0.0,-1.3,0.0);
	if(vflag==1)
	{
		zt+=0.06;
	}
	if(vflag==2)
	{
		zt-=0.06;
	}
	if(vflag==3)
	{
		xt += 0.05;
	}
	if(vflag==4)
	{
		xt -= 0.05;
	}
	if(vflag==5)
	{
		incy+=0.06;
	}
	if(vflag==6)
	{
		incy-=0.06;
	}
	if(vflag==7)
	{
		incx += 0.05;
	}
	if(vflag==8)
	{
		incx -= 0.05;
	}
	
	vflag=0;
	glTranslatef(xt,yt,zt);

	Draw_sky();
	Draw_ground();

	
	draw_circle(0.7,1,0,0);
	draw_circle(0.5,1,1,0);
	draw_circle(0.35,1,0.5,0.3);
	draw_circle(0.25,0,0,1);
	draw_circle(0.2,0,1,0);
	
	draw_angle_board();
	Arrow();
	speed_bar();
	glPushMatrix();
	glTranslatef(0.0,-1.3,-6.0);
	Score();
	glPopMatrix();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}
void menu1()				//Starting menu
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glClearColor(0,0,0,0.0);
	glTranslatef(0.0,0.0,-6.0);
	glTranslatef(0.0,-1.3,0.0);
	glColor3f(1.00,0.20,0.10);
	glLoadName(TEXTID);
	s = " HIT THE SPOT ";
	DrawTextXY(-2.7,3.0,0.0,0.003);
	glColor3f(0.6,0.8,0.7);
	s = " MENU ";
	DrawTextXY(-1.25,2.4,0.0,0.0014);
	glColor3f(1.0,0.8,0.4);
	s = " 1 : PLAY ";
	DrawTextXY(-1.25,2.1,0.0,0.001);
	s = " 2 : HELP ";
	DrawTextXY(-1.25,1.9,0.0,0.001);
	s = " 3 : EXIT ";
	DrawTextXY(-1.25,1.7,0.0,0.001);
	glFlush();
	glutSwapBuffers();
}
void menu2()			//Help menu		
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glClearColor(0,0,0,1.0);
	glTranslatef(0.0,0.0,-6.0);
	glTranslatef(0.0,-1.3,0.0);
	glColor3f(0.6,0.8,0.7);
	s = " HELP ";
	DrawTextXY(-1.25,2.7,0.0,0.003);
	glColor3f(1.0,0.8,0.4);
	s = " FRONT - UP Arrow ";
	DrawTextXY(-1.25,2.3,0.0,0.001);
	s = " BACK - Down Arrow ";
	DrawTextXY(-1.25,2.1,0.0,0.001);
	s = " LEFT - Left Arrow ";
	DrawTextXY(-1.25,1.9,0.0,0.001);
	s = " RIGHT - Right Arrow ";
	DrawTextXY(-1.25,1.7,0.0,0.001);
	s = " Adjust speed - a ";
	DrawTextXY(-1.25,1.5,0.0,0.001);
	s = " Press ENTER to shoot ";
	DrawTextXY(-1.25,1.3,0.0,0.001);

	glFlush();
	glutSwapBuffers();
}

void menu3()			//Gameover menu
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0,0.0,-6.0);
	glTranslatef(0.0,-1.3,0.0);
	glColor3f(0.6,0.8,0.7);
	s = " Game Over.... ";
	DrawTextXY(-1.25,2.7,0.0,0.002);
	stringstream out3;
	glColor3f(0.6,0.8,0.7);
	s = " Score ";
	DrawTextXY(-1.25,2.1,0.0,0.002);
	out3 << scr;
	s = out3.str();
	DrawTextXY(0.0,2.1,0.0,0.002);
	glColor3f(0.6,0.8,0.7);
	s = " Enter to continue... ";
	DrawTextXY(-1.25,1.7,0.0,0.002);
	glFlush();
	glutSwapBuffers();
}

void Dis()
{
	if(f==0){
		menu1();
		A_left=5;
	}
	else if(f==1)
		menu2();
	else if(f==2)
		menu3();
	else
		Display();
}
void Reshape(int x, int y)    //To handle the window resizes
{
	if (y == 0 || x == 0) return;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(GLdouble)x/(GLdouble)y,0.10,20.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,x,y);
	glPointSize(GLfloat(x)/600.0);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1440,720);
	glutInitWindowPosition(0,0);
	glutCreateWindow("3D-Archery");
	initGL();
	initTexture();
	glutDisplayFunc(Dis);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(NormalKey);
	glutSpecialFunc(SpecialKey);
	glutIdleFunc(Dis);
	glutMainLoop();
	return 0;
}

