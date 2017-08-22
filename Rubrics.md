# PID Controller

#### Rubric 1 - Code Should Compile
All necessary files have been checked in to build the project.

#### Rubric 2 - Implementation
Two main files where I have written most of the code. Error calculation is in PID.cpp 

```C++
void PID::UpdateError(double cte) {
	d_error = cte - p_error;
	p_error = cte;
	i_error += cte;
}
```

In main.cpp the steer value is caculated based on the provided error value

```C++
pid.UpdateError(cte);
steer_value = -pid.Kp * cte - pid.Kd * pid.d_error - pid.Ki * pid.i_error;
steer_value = max(min(1.0, steer_value), -1.0);
```

#### Rubric 3 - Reflection
As the name suggests that PID controller has three elements P, I and D. The goal in our context
is to keep the car in the center of the lane and keep it from drifting to the edges while preventing excessive oscillation.
 
To do that the first thing we do is to offset the error by **Proportion** to the error to correct the trajectory. No 
matter how smaller the coefficient is its bound to overshoot a little. Larger the coefficient the more it oscillates.
  
To Address that the **Differential** controller which makes it a PD controller counter steers over time (CTE derivative wrt time) 
so we gracefully approach the target trajectory. 

This leads us to third part of the controller that is **Integral** controller which address that systematic Bias and counter 
 the effect of constant drift using CTE.

  
##### Co-Efficient Selection

For this project I pretty much used a manual calculation to achieve the goal. Started with values closer to what experimented
during the lectures. I tried to swing the values to extremes to measure the effect and then selected a moderate value that 
provided the desired result that is keep the car in the middle with least amount of oscillation.

Here are some sample vidoes.


|Sample Videos|Kp,Ki,Kd|
| ------------- |-------------|
|[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/YOUTUBE_VIDEO_ID_HERE/0.jpg)](https://youtu.be/LQhpuLInvAk)|1.0, 0.0004, 7.0 - Over correcting|
|[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/YOUTUBE_VIDEO_ID_HERE/0.jpg)](https://youtu.be/f678RolrkSs)|0.2, 0.0004, 1.0 - Speedy approach to trajectory|
|[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/YOUTUBE_VIDEO_ID_HERE/0.jpg)](https://youtu.be/nBppfHs0wYk)|0.3, 0.0005, 7.0 - Selected Values|

 
#### Rubric 4 - Simulation
Checked on the simulator to verify that it completes a full lap without touching the edges. 