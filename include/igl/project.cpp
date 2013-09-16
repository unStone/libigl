#include "project.h"
#ifndef IGL_NO_OPENGL
#include <iostream>
#include "report_gl_error.h"

#include "OpenGL_convenience.h"

IGL_INLINE int igl::project(
  const double objX,
  const double objY,
  const double objZ,
  double* winX,
  double* winY,
  double* winZ)
{
  using namespace std;
#ifdef EXTREME_VERBOSE
  cout<<"project();"<<endl;
#endif
  // Put model, projection, and viewport matrices into double arrays
  double MV[16];
  double P[16];
  int VP[4];
  glGetDoublev(GL_MODELVIEW_MATRIX,  MV);

#ifdef EXTREME_VERBOSE
  cout<<"MV=["<<endl<<
    MV[0]<<" "<< MV[1]<<" "<< MV[2]<<" "<< MV[3]<<" "<<endl<<
    MV[4]<<" "<< MV[5]<<" "<< MV[6]<<" "<< MV[7]<<" "<<endl<<
    MV[8]<<" "<< MV[9]<<" "<< MV[10]<<" "<< MV[11]<<" "<<endl<<
    MV[12]<<" "<< MV[13]<<" "<< MV[14]<<" "<< MV[15]<<" "<<endl<<
    "];"<<endl;
#endif
#ifndef NDEBUG
  igl::report_gl_error();
#endif

  glGetDoublev(GL_PROJECTION_MATRIX, P);

#ifdef EXTREME_VERBOSE
  cout<<"P=["<<endl<<
    P[0]<<" "<< P[1]<<" "<< P[2]<<" "<< P[3]<<" "<<endl<<
    P[4]<<" "<< P[5]<<" "<< P[6]<<" "<< P[7]<<" "<<endl<<
    P[8]<<" "<< P[9]<<" "<< P[10]<<" "<< P[11]<<" "<<endl<<
    P[12]<<" "<< P[13]<<" "<< P[14]<<" "<< P[15]<<" "<<endl<<
    "];"<<endl;
#endif
#ifndef NDEBUG
  igl::report_gl_error();
#endif

  glGetIntegerv(GL_VIEWPORT, VP);

#ifdef EXTREME_VERBOSE
  cout<<"VP=["<<endl<<
    VP[0]<<" "<< VP[1]<<" "<< VP[2]<<" "<< VP[3]<<" "<<endl<<
    "];"<<endl;
#endif
#ifndef NDEBUG
  igl::report_gl_error();
#endif

  return gluProject(objX,objY,objZ,MV,P,VP,winX,winY,winZ);
}

template <typename Derivedobj, typename Derivedwin>
IGL_INLINE int igl::project(
  const Eigen::PlainObjectBase<Derivedobj> & obj,
  Eigen::PlainObjectBase<Derivedwin> & win)
{
  return igl::project(obj(0),obj(1),obj(2),&win(0),&win(1),&win(2));
}

#ifndef IGL_HEADER_ONLY
// Explicit template instanciations
template int igl::project<Eigen::Matrix<double, 3, 1, 0, 3, 1>, Eigen::Matrix<double, 3, 1, 0, 3, 1> >(Eigen::PlainObjectBase<Eigen::Matrix<double, 3, 1, 0, 3, 1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, 3, 1, 0, 3, 1> >&);
#endif

#endif
