#include <GL/glut.h>
#include <math.h>

static int shoulderlz = 0, elbowl = 0, shoulderrz = 0, elbowr = 0 , kneel = 0 , kneer = 0 ,
            hiblz = 0 , hibrx = 0 , shoulderlx = 0, shoulderrx = 0 ,
            hiblx = 0 , hibrz = 0 , fingerBaser = 0, fingerUpr = 0,fingerBaser2=0,fingerUpr2=0,fingerBaser3=0,fingerUpr3=0,
fingerBaser4=0,fingerUpr4=0,fingerBaser5=0,fingerUpr5=0 , fingerBasel = 0, fingerUpl = 0,fingerBasel2=0,fingerUpl2=0,fingerBasel3=0,fingerUpl3=0,
fingerBasel4=0,fingerUpl4=0,fingerBasel5=0,fingerUpl5=0 ;
double eye[] = { 0, 0, -20 };
double center[] = { 0, 0, 1 };
double up[] = { 0, 1, 0 };
double direction[]={0,0,0};
double new[]={0,0,0};
double newt[]={0,0,0};
int moving, startx;
GLfloat angle = 0.0;   /* in degrees */
void ArmL (void);
void ArmR (void);
void LegL (void);
void LegR (void);
void BodyAndHead (void);
void init(void)
{
   glMatrixMode(GL_PROJECTION);
	gluPerspective(65.0, (GLfloat)1024 / (GLfloat)869, 1.0, 60.0);
}

void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}

void rotatePoint(double a[], double theta, double p[])
{

	double temp[3];
	temp[0] = p[0];
	temp[1] = p[1];
	temp[2] = p[2];

	temp[0] = -a[2] * p[1] + a[1] * p[2];
	temp[1] = a[2] * p[0] - a[0] * p[2];
	temp[2] = -a[1] * p[0] + a[0] * p[1];

	temp[0] *= sin(theta);
	temp[1] *= sin(theta);
	temp[2] *= sin(theta);

	temp[0] += (1 - cos(theta))*(a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta))*(a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta))*(a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta)*p[0];
	temp[1] += cos(theta)*p[1];
	temp[2] += cos(theta)*p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];
}

void Left()
{  
	rotatePoint(up,0.1,eye);
	// implement camera rotation arround vertical window screen axis to the left
	// used by mouse and left arrow
}

void Right()
{
	rotatePoint(up,-0.1,eye);
	// implement camera rotation arround vertical window screen axis to the right
	// used by mouse and right arrow
}

void Up()
{
	crossProduct(eye,up,new);
	normalize(new);
	rotatePoint(new , 0.1,eye);
	// implement camera rotation arround horizontal window screen axis +ve
	// used by up arrow
}

void Down()
{	
	crossProduct(eye,up,newt);
	normalize(newt);
	rotatePoint(newt , -0.1,eye);
	// implement camera rotation arround horizontal window screen axis 
	// used by down arrow
}

void moveForward()
{
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];
	eye[0]    += direction[0] * 0.1;
	eye[1]    += direction[1] * 0.1;
	eye[2]    += direction[2] * 0.1;
}

void moveBack()
{
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];
	eye[0]    -= direction[0] * 0.1;
	eye[1]    -= direction[1] * 0.1;
	eye[2]    -= direction[2] * 0.1;
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT );
   glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
	glPushMatrix();
   glRotatef(angle, 0.0, 1.0, 0.0);

   glPushMatrix();
   
   BodyAndHead();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-1.25,1.0,0.0); 
   ArmL();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(1.25,1.0,0.0);
   ArmR();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-0.5,-2.0,0.0);
   LegL();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.5,-2.0,0.0);
   LegR();
   glPopMatrix();
   
   glPopMatrix();
	glutSwapBuffers();
}
void ArmL (void)
{
   // shoulder part 

   glRotatef ((GLfloat) shoulderlx, 1.0, 0.0, 0.0);

   glTranslatef (0.5, 0.0, 0.0);
   glRotatef ((GLfloat) shoulderlz, 0.0, 0.0, 1.0);
   glTranslatef (-0.5, 0.0, 0.0);
   glPushMatrix();
   glScalef (1.0, 0.3, 0.2);
   glutWireCube (1.0);
   glPopMatrix();
   // elbow part
   glTranslatef (-0.5, 0.0, 0.0);
   glRotatef ((GLfloat) elbowl, 0.0, 0.0, 1.0);
   glTranslatef (-0.5, 0.0, 0.0);
   glPushMatrix();
   glScalef (1.0, 0.3, 0.2);
   glutWireCube (1.0);
   glPopMatrix();

   //Draw finger flang 1 
   glPushMatrix();
   glTranslatef(-0.5, 0.125, -0.08);
   glRotatef((GLfloat)fingerBasel, 0.0, 1.0, 0.0);
   glTranslatef(-0.075, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.15, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();


   //Draw finger flang 1 
   
   glTranslatef(-0.075, 0.0, 0.0);
   glRotatef((GLfloat)fingerUpl, 0.0, 1.0, 0.0);
   glTranslatef(-0.05, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.1, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();
   glPopMatrix();

   //Draw finger flang 2 
   glPushMatrix();
   
   glTranslatef(-0.5, 0.05, -0.08);
   glRotatef((GLfloat)fingerBasel2, 0.0, 1.0, 0.0);
   glTranslatef(-0.075, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.15, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();


   //Draw finger flang 2 
   glTranslatef(-0.05, 0.0, 0.0);
   glRotatef((GLfloat)fingerUpl2, 0.0, 1.0, 0.0);
   glTranslatef(-0.05, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.1, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();
   glPopMatrix();

   //Draw finger flang 3
   glPushMatrix();

   glTranslatef(-0.5, -0.03, -0.08);
   glRotatef((GLfloat)fingerBasel3, 0.0, 1.0, 0.0);
   glTranslatef(-0.075, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.15, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();


   //Draw finger flang 3 
   glTranslatef(-0.05, 0.0, 0.0);
   glRotatef((GLfloat)fingerUpl3, 0.0, 1.0, 0.0);
   glTranslatef(-0.05, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.1, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();
   glPopMatrix();

   //Draw finger flang 4
   glPushMatrix();

   glTranslatef(-0.5, -0.125, -0.08);
   glRotatef((GLfloat)fingerBasel4, 0.0, 1.0, 0.0);
   glTranslatef(-0.075, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.15, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();


   //Draw finger flang 4
   glTranslatef(-0.05, 0.0, 0.0);
   glRotatef((GLfloat)fingerUpl4, 0.0, 1.0, 0.0);
   glTranslatef(-0.05, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.1, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();
   glPopMatrix();

   //Draw finger flang 5
   glPushMatrix();

   glTranslatef(-0.5, 0.125, 0.08);
   glRotatef((GLfloat)fingerBasel5, 0.0, 1.0, 0.0);
   glTranslatef(-0.075, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.15, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();


   //Draw finger flang 5 
   glTranslatef(-0.05, 0.0, 0.0);
   glRotatef((GLfloat)fingerUpl5, 0.0, 1.0, 0.0);
   glTranslatef(-0.05, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.1, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();
   glPopMatrix();
};
void ArmR (void)
{
   // Shoulder part 

   glRotatef ((GLfloat) shoulderrx, 1.0, 0.0, 0.0);

   glTranslatef (-0.5, 0.0, 0.0);
   glRotatef ((GLfloat) shoulderrz, 0.0, 0.0, 1.0);
   glTranslatef (0.5, 0.0, 0.0);
   glPushMatrix();
   glScalef (1.0, 0.3, 0.2);
   glutWireCube (1.0);
   glPopMatrix();
   // Elbow part 
   glTranslatef (0.5, 0.0, 0.0); 
   glRotatef ((GLfloat) elbowr, 0.0, 0.0, 1.0);
   glTranslatef (0.5, 0.0, 0.0);
   glPushMatrix();
   glScalef (1.0, 0.3, 0.2);
   glutWireCube (1.0);
   glPopMatrix();

   //Draw finger flang 1 
   glPushMatrix();
   glTranslatef(0.5, 0.125, -0.08);
   glRotatef((GLfloat)fingerBaser, 0.0, 1.0, 0.0);
   glTranslatef(0.075, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.15, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();


   //Draw finger flang 1 
   
   glTranslatef(0.05, 0.0, 0.0);
   glRotatef((GLfloat)fingerUpr, 0.0, 1.0, 0.0);
   glTranslatef(0.05, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.1, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();
   glPopMatrix();

   //Draw finger flang 2 
   glPushMatrix();
   
   glTranslatef(0.5, 0.05, -0.08);
   glRotatef((GLfloat)fingerBaser2, 0.0, 1.0, 0.0);
   glTranslatef(0.075, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.15, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();


   //Draw finger flang 2 
   glTranslatef(0.05, 0.0, 0.0);
   glRotatef((GLfloat)fingerUpr2, 0.0, 1.0, 0.0);
   glTranslatef(0.05, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.1, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();
   glPopMatrix();

   //Draw finger flang 3
   glPushMatrix();

   glTranslatef(0.5, -0.03, -0.08);
   glRotatef((GLfloat)fingerBaser3, 0.0, 1.0, 0.0);
   glTranslatef(0.075, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.15, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();


   //Draw finger flang 3 
   glTranslatef(0.05, 0.0, 0.0);
   glRotatef((GLfloat)fingerUpr3, 0.0, 1.0, 0.0);
   glTranslatef(0.05, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.1, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();
   glPopMatrix();

   //Draw finger flang 4
   glPushMatrix();

   glTranslatef(0.5, -0.125, -0.08);
   glRotatef((GLfloat)fingerBaser4, 0.0, 1.0, 0.0);
   glTranslatef(0.075, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.15, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();


   //Draw finger flang 4
   glTranslatef(0.05, 0.0, 0.0);
   glRotatef((GLfloat)fingerUpr4, 0.0, 1.0, 0.0);
   glTranslatef(0.05, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.1, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();
   glPopMatrix();

   //Draw finger flang 5
   glPushMatrix();

   glTranslatef(0.5, 0.125, 0.08);
   glRotatef((GLfloat)fingerBaser5, 0.0, 1.0, 0.0);
   glTranslatef(0.075, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.15, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();


   //Draw finger flang 5 
   glTranslatef(0.05, 0.0, 0.0);
   glRotatef((GLfloat)fingerUpr5, 0.0, 1.0, 0.0);
   glTranslatef(0.05, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.1, 0.05, 0.05);
   glutWireCube(1);
   glPopMatrix();
   glPopMatrix();
};
void BodyAndHead (void)
{
   glPushMatrix();
   glScalef (1.5, 2.5, 0.8);
   glutWireCube (1.0);
   glPopMatrix();
   glTranslatef (0.0, 1.75, 0.0);
   glPushMatrix();
   glutWireSphere (0.4,10.0,10.0);
   glPopMatrix();
};
void LegL (void)
{  
   // hips part 
   
   glTranslatef (0.0, 0.75, 0.0);
   glRotatef ((GLfloat) hiblx, 1.0, 0.0, 0.0);
   glTranslatef (0.0, -0.75, 0.0);
   
   glTranslatef (0.0, 0.75, 0.0);
   glRotatef ((GLfloat) hiblz, 0.0, 0.0, 1.0);
   glTranslatef (0.0, -0.75, 0.0);
   
   glPushMatrix();
   glScalef (0.5, 1.5, 0.8);
   glutWireCube (1.0);
   glPopMatrix();
   // knee part 
   glTranslatef (0.0, -0.75, 0.0); 
   glRotatef ((GLfloat) kneel, 1.0, 0.0, 0.0);
   glTranslatef (0.0, -0.75, 0.0);
   glPushMatrix();
   glScalef (0.5, 1.5, 0.8);
   glutWireCube (1.0);
   glPopMatrix();
   // feet part
   glTranslatef (0.0, -1.0, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.5, 1.8);
   glutSolidCube (1.0);
   glPopMatrix();
}
void LegR (void)
{  
   // hips part 
   glTranslatef (0.0, 0.75, 0.0);
   glRotatef ((GLfloat) hibrx, 1.0, 0.0, 0.0);
   glTranslatef (0.0, -0.75, 0.0);
   
   glTranslatef (0.0, 0.75, 0.0);
   glRotatef ((GLfloat) hibrz, 0.0, 0.0, 1.0);
   glTranslatef (0.0, -0.75, 0.0);

   glPushMatrix();
   glScalef (0.5, 1.5, 0.8);
   glutWireCube (1.0);
   glPopMatrix();
   // knee part 
   glTranslatef (0.0, -0.75, 0.0); 
   glRotatef ((GLfloat) kneer, 1.0, 0.0, 0.0);
   glTranslatef (0.0, -0.75, 0.0);
   glPushMatrix();
   glScalef (0.5, 1.5, 0.8);
   glutWireCube (1.0);
   glPopMatrix();
   // feet part
   glTranslatef (0.0, -1.0, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.5, 1.8);
   glutSolidCube (1.0);
   glPopMatrix();
}
void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT: 
	Left();
   // glutPostRedisplay();
	 break;
	case GLUT_KEY_RIGHT: 
	Right();
   // glutPostRedisplay(); 
   break;
	case GLUT_KEY_UP:
	Up(); 
   // glutPostRedisplay();
   break;
	case GLUT_KEY_DOWN:  
	Down(); 
   // glutPostRedisplay();
   break;
	}
   glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	// List all youe keyboard keys from assignment two her for body movement
	switch (key)
	{
	case 'f':
		moveForward();
		glutPostRedisplay();
		break;
	case 'b':
		moveBack();
		glutPostRedisplay();
		break;
	case '1':
   if(fingerBasel<=-5) break;
   else
   {
      fingerBasel = (fingerBasel - 5) % 10;
      glutPostRedisplay();
      break;
   }   
   case '!':
   if(fingerBasel>=40) break;
   else
   {
   
      fingerBasel = (fingerBasel + 5) % 45;
      glutPostRedisplay();
      break;  
   }
   
   case '2':
   if(fingerUpl<=-5) break;
   else
   {
      fingerUpl = (fingerUpl - 5) % 10;
      glutPostRedisplay();
      break;
   }
   case '@':
   if(fingerUpl>=85) break;
   else
   { 
      fingerUpl = (fingerUpl + 5) % 90;
      glutPostRedisplay();
      break;
   }
   case '3':
   if(fingerBasel2<=-5) break;
   else
   {
      fingerBasel2 = (fingerBasel2 - 5) % 10;
      glutPostRedisplay();
      break;
   }
   case '#':
   if(fingerBasel2>=40) break;
   else
   {
      fingerBasel2 = (fingerBasel2 + 5) % 45;
      glutPostRedisplay();
      break;  
   }
   case '4':
   if(fingerUpl2<=-5) break;
   else
   {
      fingerUpl2 = (fingerUpl2 - 5) % 10;
      glutPostRedisplay();
      break;
   }
   case '$':
   if(fingerUpl2>=85) break;
   else
   {
      fingerUpl2 = (fingerUpl2 + 5) % 90;
      glutPostRedisplay();
      break;
   }
   case '5':
   if(fingerBasel3<=-5) break;
   else
   {
   
      fingerBasel3 = (fingerBasel3 - 5) % 10;
      glutPostRedisplay();
      break;
   }
   case '%':
   if(fingerBasel3>=40) break;
   else
   {
   
      fingerBasel3 = (fingerBasel3 + 5) % 45;
      glutPostRedisplay();
      break;  
   }
   case '6':
   if(fingerUpl3<=-5) break;
   else
   {
   
      fingerUpl3 = (fingerUpl3 - 5) % 10;
      glutPostRedisplay();
      break;
   }
   case '^':
   if(fingerUpl3>=85) break;
   else
   {
   
      fingerUpl3 = (fingerUpl3 + 5) % 90;
      glutPostRedisplay();
      break;   
   }
   case '7':
    if(fingerBasel4<=-5) break;
   else
   {
      fingerBasel4 = (fingerBasel4 - 5) % 10;
      glutPostRedisplay();
      break;
   }
   case '&':

    if(fingerBasel4>=40) break;
   else
   {
      fingerBasel4 = (fingerBasel4 + 5) % 45;
      glutPostRedisplay();
      break;  
   }
   case '8':
   if(fingerUpl4<=-5) break;
   else
   {
      fingerUpl4 = (fingerUpl4 - 5) % 10;
      glutPostRedisplay();
      break;
   }
   case '*':
   if(fingerUpl4>=85) break;
   else
   {
   
      fingerUpl4 = (fingerUpl4 + 5) % 90;
      glutPostRedisplay();
      break; 
   }
   case '9':
   if(fingerBasel5<=-40) break;
   else
   {
   
      fingerBasel5 = (fingerBasel5 - 5) % 45;
      glutPostRedisplay();
      break;
   }
   case '(':
   if(fingerBasel5>=5) break;
   else
   {
   
      fingerBasel5 = (fingerBasel5 + 5) % 10;
      glutPostRedisplay();
      break;  
   }
   case '0':
   if(fingerUpl5<=-85) break;
   else
   {
   
      fingerUpl5 = (fingerUpl5 - 5) % 90;
      glutPostRedisplay();
      break;
   }
   case ')':
   if(fingerUpl5>=5) break;
   else
   {
   
      fingerUpl5 = (fingerUpl5 + 5) % 10;
      glutPostRedisplay();
      break;       
   }
   case 'q':
   if(fingerBaser>=5) break;
   else
   {
   
      fingerBaser = (fingerBaser + 5) % 10;
      glutPostRedisplay();
      break;
   }
   case 'Q':
   if(fingerBaser<=-40) break;
   else
   {
   
      fingerBaser = (fingerBaser - 5) % 45;
      glutPostRedisplay();
      break;  
   }
   case 'w':
   if(fingerUpr>=5) break;
   else
   {
   
      fingerUpr = (fingerUpr + 5) % 10;
      glutPostRedisplay();
      break;
   }
   case 'W':
   if(fingerUpr<=-85) break;
   else
   {
   
      fingerUpr = (fingerUpr - 5) % 90;
      glutPostRedisplay();
      break; 
   }
   case 't':
   if(fingerBaser2>=5) break;
   else
   {
   
      fingerBaser2 = (fingerBaser2 + 5) % 10;
      glutPostRedisplay();
      break;
   }
   case 'T':
   if(fingerBaser2<=-40) break;
   else
   {
   
      fingerBaser2 = (fingerBaser2 - 5) % 45;
      glutPostRedisplay();
      break;  
   }
   case 'y':
   if(fingerUpr2>=5) break;
   else
   {
   
      fingerUpr2 = (fingerUpr2 + 5) % 10;
      glutPostRedisplay();
      break;
   }
   case 'Y':
   if(fingerUpr2<=-85) break;
   else
   {
   
      fingerUpr2 = (fingerUpr2 - 5) % 90;
      glutPostRedisplay();
      break;  
   }
   case 'u':
   if(fingerBaser3>=5) break;
   else
   {
   
      fingerBaser3 = (fingerBaser3 + 5) % 10;
      glutPostRedisplay();
      break;
   }
   case 'U':
   if(fingerBaser3<=-40) break;
   else
   {
   
      fingerBaser3 = (fingerBaser3 - 5) % 45;
      glutPostRedisplay();
      break;  
   }
   case 'i':
   if(fingerUpr3>=5) break;
   else
   {
   
      fingerUpr3 = (fingerUpr3 + 5) % 10;
      glutPostRedisplay();
      break;
   }
   case 'I':
   if(fingerUpr3<=-85) break;
   else
   {
   
      fingerUpr3 = (fingerUpr3 - 5) % 90;
      glutPostRedisplay();
      break;     
   }
   case 'o':
   if(fingerBaser4>=5) break;
   else
   {
   
      fingerBaser4 = (fingerBaser4 + 5) % 10;
      glutPostRedisplay();
      break;
   }
   case 'O':
   if(fingerBaser4<=-40) break;
   else
   {
   
      fingerBaser4 = (fingerBaser4 - 5) % 45;
      glutPostRedisplay();
      break;  
   }
   case 'p':
   if(fingerUpr4>=5) break;
   else
   {
   
      fingerUpr4 = (fingerUpr4 + 5) % 10;
      glutPostRedisplay();
      break;
   }
   case 'P':
   if(fingerUpr4<=-85) break;
   else
   {
   
      fingerUpr4 = (fingerUpr4 - 5) % 90;
      glutPostRedisplay();
      break;     
   }
   case '[':
   if(fingerBaser5>=40) break;
   else
   {
   
      fingerBaser5 = (fingerBaser5 + 5) % 45;
      glutPostRedisplay();
      break;
   }
   case '{':
   if(fingerBaser5<=-5) break;
   else
   {
   
      fingerBaser5 = (fingerBaser5 - 5) % 10;
      glutPostRedisplay();
      break;  
   }
   case ']':
   if(fingerUpr5>=85) break;
   else
   {
   
      fingerUpr5 = (fingerUpr5 + 5) % 90;
      glutPostRedisplay();
      break;
   }
   case '}':
   if(fingerUpr5<=-5) break;
   else
   {
   
      fingerUpr5 = (fingerUpr5 - 5) % 10;
      glutPostRedisplay();
      break;    
   }
   case 's':
   if(shoulderrz>=75) break;
   else
   {
   
      shoulderrz = (shoulderrz + 5) % 80;
      glutPostRedisplay();
      break;
   }
   case 'S':
   if(shoulderrz<=-70) break;
   else
   {
    
      shoulderrz = (shoulderrz - 5) % 75;
      glutPostRedisplay();
      break;
   }
   case 'z':
   if(shoulderrx>=175) break;
   else
   {
   
      shoulderrx = (shoulderrx + 5) % 180;
      glutPostRedisplay();
      break;
   }
   case 'Z':
      if(shoulderrx<=-5) break;
   else
   {
   
      shoulderrx = (shoulderrx - 5) % 10;
      glutPostRedisplay();
      break;   
   }
   case 'e':
   if(elbowr>=85) break;
   else
   {
   
      elbowr = (elbowr + 5) % 90;
      glutPostRedisplay();
      break;
   }
   case 'E':
   if(elbowr<=-5) break;
   else
   {
   
      elbowr = (elbowr - 5) % 10;
      glutPostRedisplay();
      break;
   }
   case 'd':
   if(shoulderlz>=70) break;
   else
   {
   
      shoulderlz = (shoulderlz + 5) % 75;
      glutPostRedisplay();
      break;
   }
   case 'D':
   if(shoulderlz<=-75) break;
   else
   {
   
      shoulderlz = (shoulderlz - 5) % 80;
      glutPostRedisplay();
      break;
   }
   case 'x':
   if(shoulderlx>=175) break;
   else
   {
   
      shoulderlx = (shoulderlx + 5) % 180;
      glutPostRedisplay();
      break;
   }
   case 'X':
   if(shoulderlx<=-5) break;
   else
   {
   
      shoulderlx = (shoulderlx - 5) % 10;
      glutPostRedisplay();
      break;   
   }
   case 'r':
   if(elbowl>=5) break;
   else
   {
   
      elbowl = (elbowl + 5) % 10;
      glutPostRedisplay();
      break;
   }
   case 'R':
   if(elbowl<=-85) break;
   else
   {
   
      elbowl = (elbowl - 5) % 90;
      glutPostRedisplay();
      break;   
   }
   case 'h':
   if(hiblx>=55) break;
   else
   {
   
      hiblx = (hiblx + 5) % 60;
      glutPostRedisplay();
      break;
   }
   case 'H':
   if(hiblx<=-85) break;
   else
   {
   
      hiblx = (hiblx - 5) % 90;
      glutPostRedisplay();
      break;
   }
   case 'j':
   if(hiblz>=10) break;
   else
   {
   
      hiblz = (hiblz + 5) % 15;
      glutPostRedisplay();
      break;
   }
   case 'J':
   if(hiblz<=-60) break;
   else
   {
   
      hiblz = (hiblz - 5) % 65;
      glutPostRedisplay();
      break;
   }
   case 'k':
   if(kneel>=85) break;
   else
   {
   
      kneel = (kneel + 5) % 90;
      glutPostRedisplay();
      break;
   }
   case 'K':
   if(kneel<=-5) break;
   else
   {
   
      kneel = (kneel - 5) % 10;
      glutPostRedisplay();
      break;  
   }
   case 'v':
   if(hibrx>=55) break;
   else
   {
   
      hibrx = (hibrx + 5) % 60;
      glutPostRedisplay();
      break;
   }
   case 'V':
   if(hibrx<=-85) break;
   else
   {
   
      hibrx = (hibrx - 5) % 90;
      glutPostRedisplay();
      break;
   }
   case 'n':
   if(hibrz>=60) break;
   else
   {
   
      hibrz = (hibrz + 5) % 65;
      glutPostRedisplay();
      break;
   }
   case 'N':
   if(hibrz<=-10) break;
   else
   {
   
      hibrz = (hibrz - 5) % 15;
      glutPostRedisplay();
      break;
   }
   case 'm':
   if(kneer>=85) break;
   else
   {
   
      kneer = (kneer + 5) % 90;
      glutPostRedisplay();
      break;
   }
   case 'M':
   if(kneer<=-10) break;
   else
   {
   
      kneer = (kneer - 5) % 15;
      glutPostRedisplay();
      break;  	
   }
   default:
		break;

	}
}
static void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON) {
      moving = 1;
      startx = x;
    }
  
}


static void motion(int x, int y)
{
  if (moving) {
    angle = angle + (x - startx);
    startx = x;
    glutPostRedisplay();
  }
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("body");
	init();
   glutMouseFunc(mouse);
   glutMotionFunc(motion);
	glutDisplayFunc(display);
   glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}
