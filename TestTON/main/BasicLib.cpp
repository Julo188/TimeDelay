/*
 * BasicLib.cpp
 *
 *  Created on: 25.08.2021
 *      Author: FranzHoepfinger
 */



#include <stdbool.h>
#include <stdint.h>
#include "TimeLib.h"
#include "StandardLib.h"
#include "BasicLib.h"

bool CLICK_DEC::operator ()(bool IN)
{
	/* Q shall only be active for one cycle only */
	if (IN == false)
	{
		Q0 = false;
		Q1 = false;
		Q2 = false;
		Q3 = false;
	}

	IF in AND NOT edge AND NOT tx.q THEN
		/* a rising edge on in sets the counter to 0 */
		cnt := 0;
	ELSIF tx.Q AND NOT IN AND edge THEN
		/* count falling edges when tp.q is true */
		cnt := cnt + 1;
	ELSIF NOT tx.Q THEN
		CASE cnt OF
			0 : Q0 := TRUE;
			1 : Q1 := TRUE;
			2 : Q2 := TRUE;
			3 : Q3 := TRUE;
		END_CASE;
		cnt := -1;
	END_IF;

	/* remember the status of IN */
	edge := IN;
	tx(in := IN, pt := TC);



}
