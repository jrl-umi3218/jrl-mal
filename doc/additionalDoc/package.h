/**
\mainpage

\section intro Introduction

As different implementations of linear algebra computation exist, compatibility 
between software modules using matrices and vectors is an issue.

This package implements an abstraction layer for matrix and vector computations.
Two categories of objects are supported:
\li matrices and vectors of size 3 and 4, mainly to represent rigid-body motion in space and
\li any size matrices and vectors.

For each category, two implementations are proposed and chosen at configuration. Others 
implementations can of course be added if needed.

\section implementation Implementations

\subsection boost-vnl General purpose matrices and vectors

For general purpose matrices and vectors, two implementations are proposed
\li boost implementation uses lapack
\li VNL implementation

\subsection small Small size matrices and vectors
\li \c t3d is a LAAS implementation of rigid-body transformations
\li \c jrlMathTools implements vectors and square matrices of dimension 3 and 4. Note that these matrices
do not necessarily represent rigid-body transformations.

*/
