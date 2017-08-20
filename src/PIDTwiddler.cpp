/*
 * PIDTwiddler.cpp
 *
 *  Created on: Aug 19, 2017
 *      Author: rkamran
 */

#include "PIDTwiddler.h"

PIDTwiddler::PIDTwiddler(int steps) {
	bestError = 0.0;
	newError = 0.0;

	for(int i=0; i < sizeof(p); ++i){
		p[i] = 0.0;
		dp[i] = 0.0;
	}

	this->steps = steps;
	isIntialized = false;
	isReady = false;
}

PIDTwiddler::~PIDTwiddler() {

}


void PIDTwiddler::twiddle(double error){

	if(isReady)
		return;

	//--> If we don't have the errors for total steps for twiddler
	if(!isIntialized){
		bestError += error*error;
		if(++current_step == steps){
			isIntialized = true;
			current_step = 1;
		}
		return;
	}

	//--> Once initialized then every 50 steps update the values of p
	if(current_step != steps){
		newError += error*error;
		++current_step;
	}
	else{
		if (current_step == 2*steps){
			if(++tuneIndex == sizeof(p)){
				isReady = true;
				return;
			}
		}

	}
}

void PIDTwiddler::recalculate(int i){

}

/*
 def twiddle(tol=0.2):
    p = [0, 0, 0]
    dp = [1, 1, 1]
    robot = make_robot()
    x_trajectory, y_trajectory, best_err = run(robot, p)

    it = 0
    while sum(dp) > tol:
        print("Iteration {}, best error = {}".format(it, best_err))
        for i in range(len(p)):
            p[i] += dp[i]
            robot = make_robot()
            x_trajectory, y_trajectory, err = run(robot, p)

            if err < best_err:
                best_err = err
                dp[i] *= 1.1
            else:
                p[i] -= 2 * dp[i]
                robot = make_robot()
                x_trajectory, y_trajectory, err = run(robot, p)

                if err < best_err:
                    best_err = err
                    dp[i] *= 1.1
                else:
                    p[i] += dp[i]
                    dp[i] *= 0.9
        it += 1
    return p
 * */
