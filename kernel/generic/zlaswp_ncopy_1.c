/*********************************************************************/
/* Copyright 2009, 2010 The University of Texas at Austin.           */
/* All rights reserved.                                              */
/*                                                                   */
/* Redistribution and use in source and binary forms, with or        */
/* without modification, are permitted provided that the following   */
/* conditions are met:                                               */
/*                                                                   */
/*   1. Redistributions of source code must retain the above         */
/*      copyright notice, this list of conditions and the following  */
/*      disclaimer.                                                  */
/*                                                                   */
/*   2. Redistributions in binary form must reproduce the above      */
/*      copyright notice, this list of conditions and the following  */
/*      disclaimer in the documentation and/or other materials       */
/*      provided with the distribution.                              */
/*                                                                   */
/*    THIS  SOFTWARE IS PROVIDED  BY THE  UNIVERSITY OF  TEXAS AT    */
/*    AUSTIN  ``AS IS''  AND ANY  EXPRESS OR  IMPLIED WARRANTIES,    */
/*    INCLUDING, BUT  NOT LIMITED  TO, THE IMPLIED  WARRANTIES OF    */
/*    MERCHANTABILITY  AND FITNESS FOR  A PARTICULAR  PURPOSE ARE    */
/*    DISCLAIMED.  IN  NO EVENT SHALL THE UNIVERSITY  OF TEXAS AT    */
/*    AUSTIN OR CONTRIBUTORS BE  LIABLE FOR ANY DIRECT, INDIRECT,    */
/*    INCIDENTAL,  SPECIAL, EXEMPLARY,  OR  CONSEQUENTIAL DAMAGES    */
/*    (INCLUDING, BUT  NOT LIMITED TO,  PROCUREMENT OF SUBSTITUTE    */
/*    GOODS  OR  SERVICES; LOSS  OF  USE,  DATA,  OR PROFITS;  OR    */
/*    BUSINESS INTERRUPTION) HOWEVER CAUSED  AND ON ANY THEORY OF    */
/*    LIABILITY, WHETHER  IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*    (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY WAY OUT    */
/*    OF  THE  USE OF  THIS  SOFTWARE,  EVEN  IF ADVISED  OF  THE    */
/*    POSSIBILITY OF SUCH DAMAGE.                                    */
/*                                                                   */
/* The views and conclusions contained in the software and           */
/* documentation are those of the authors and should not be          */
/* interpreted as representing official policies, either expressed   */
/* or implied, of The University of Texas at Austin.                 */
/*********************************************************************/

#include <stdio.h>
#include "common.h"

#define a2	(a1 + 2)

int CNAME(BLASLONG n, BLASLONG k1, BLASLONG k2, FLOAT *a, BLASLONG lda, blasint *ipiv, FLOAT *buffer){

  BLASLONG i, j, ip1, ip2;
  blasint *piv;
  FLOAT *a1;
  FLOAT *b1, *b2;
  FLOAT A1, A2, A3, A4;
  FLOAT B1, B2, B3, B4;

  a -= 2;
  lda *= 2;
  k1 --;

  ipiv += k1;

  if (n  <= 0) return 0;

  j = n;
  do {
    piv = ipiv;

    a1 = a + (k1 + 1) * 2;

    ip1 = *(piv + 0) * 2;
    ip2 = *(piv + 1) * 2;
    piv += 2;

    b1 = a + ip1;
    b2 = a + ip2;

    i = ((k2 - k1) >> 1);

    if (i > 0) {
      do {
	A1 = *(a1 + 0);
	A2 = *(a1 + 1);
	A3 = *(a2 + 0);
	A4 = *(a2 + 1);
	B1 = *(b1 + 0);
	B2 = *(b1 + 1);
	B3 = *(b2 + 0);
	B4 = *(b2 + 1);

	ip1 = *(piv + 0) * 2;
	ip2 = *(piv + 1) * 2;
	piv += 2;

	if (b1 == a1) {
	    if (b2 == a2) {
	      *(buffer + 0) = A1;
	      *(buffer + 1) = A2;
	      *(buffer + 2) = A3;
	      *(buffer + 3) = A4;
	    } else {
	      *(buffer + 0) = A1;
	      *(buffer + 1) = A2;
	      *(buffer + 2) = B3;
	      *(buffer + 3) = B4;

	      *(b2 + 0) = A3;
	      *(b2 + 1) = A4;
	    }
	} else
	  if (b1 == a2) {
	      if (b2 == a2) {
		*(buffer + 0) = A3;
		*(buffer + 1) = A4;
		*(buffer + 2) = A1;
		*(buffer + 3) = A2;
	      } else {
		*(buffer + 0) = A3;
		*(buffer + 1) = A4;
		*(buffer + 2) = B3;
		*(buffer + 3) = B4;
		*(b2 + 0) = A1;
		*(b2 + 1) = A2;
	      }
	  } else {
	      if (b2 == a2) {
		*(buffer + 0) = B1;
		*(buffer + 1) = B2;
		*(buffer + 2) = A3;
		*(buffer + 3) = A4;
		*(b1 + 0) = A1;
		*(b1 + 1) = A2;
	      } else
		if (b2 == b1) {
		  *(buffer + 0) = B1;
		  *(buffer + 1) = B2;
		  *(buffer + 2) = A1;
		  *(buffer + 3) = A2;
		  *(b1 + 0) = A3;
		  *(b1 + 1) = A4;
		} else {
		  *(buffer + 0) = B1;
		  *(buffer + 1) = B2;
		  *(buffer + 2) = B3;
		  *(buffer + 3) = B4;
		  *(b1 + 0) = A1;
		  *(b1 + 1) = A2;
		  *(b2 + 0) = A3;
		  *(b2 + 1) = A4;
		}
	  }

	buffer += 4;

	b1 = a + ip1;
	b2 = a + ip2;

	a1 += 4;

	i --;
      } while (i > 0);
    }

    i = ((k2 - k1) & 1);

    if (i > 0) {
      A1 = *(a1 + 0);
      A2 = *(a1 + 1);
      B1 = *(b1 + 0);
      B2 = *(b1 + 1);

      if (a1 == b1) {
	*(buffer + 0) = A1;
	*(buffer + 1) = A2;
      } else {
	*(buffer + 0) = B1;
	*(buffer + 1) = B2;
	*(b1 + 0) = A1;
	*(b1 + 1) = A2;
      }
      buffer += 2;
    }

    a += lda;
    j --;
  } while (j > 0);

  return 0;
}

