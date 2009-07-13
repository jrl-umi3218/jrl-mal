/**
 * Produce a warning at compilation step if the MAL::boost implementation
 * is not used.
 *
 * (c) 2006 , Nicolas Mansard, Olivier Stasse JRL-Japan, CNRS-AIST, ISRI.
 */


/*!
 * \file boostspecific.h
 * Include this file to mark some part of the code where the
 * boost internal library is specificaly used. Typically when 
 * accessToMotherLib is used, the \#include <boostspecific.h> 
 * will prevent the later modification of the file toward
 * for example maal::t3d.
 */ 

#ifndef __MAAL_BOOST__

#ifdef WIN32
#pragma message ( " -- !!! -- Warning : This part of the code is only valid for the specific <boost> implementation of the MAL. If you are not using boost, the following code could produce undefined behaviors at run-time execution, or even not compile at all. Check and correct ..." )
#else
#warning "This part of the code is only valid for the specific <boost> implementation of the MAL. If you are not using boost, the following code could produce undefined behaviors at run-time execution, or even not compile at all. Check and correct ..."
#endif /* WIN32 */

#endif /* #ifndef __MAAL_BOOST__ */


