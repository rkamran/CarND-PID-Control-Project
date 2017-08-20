/*
 * PIDTwiddler.h
 *
 *  Created on: Aug 19, 2017
 *      Author: rkamran
 */

#ifndef SRC_PIDTWIDDLER_H_
#define SRC_PIDTWIDDLER_H_

class PIDTwiddler {
public:
	double p[3];
	double dp[3];


	PIDTwiddler(int steps);
	virtual ~PIDTwiddler();

	void twiddle(double error);

private:
	int tuneIndex = 0;
	bool isIntialized;
	bool isReady;
	double bestError, newError;
	int steps = 50;
	int current_step = 1;
	void recalculate(double& Kx, bool& cur_dir);
};

#endif /* SRC_PIDTWIDDLER_H_ */
