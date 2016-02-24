/*
 * IMULowpass.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: nicolas
 */

#include "IMULowpass.h"

IMULowpass::IMULowpass()
: first_time_(true),
  smoothing_factor_(1.0)
{
//	filtered_meas_.acc_duo = {0.0, 0.0, 0.0};
//	filtered_meas_.gyr_duo = {0.0, 0.0, 0.0};
}

IMULowpass::IMULowpass(double smoothing_factor)
: first_time_(true),
  smoothing_factor_(1.0)
{
	setSmoothingFactor(smoothing_factor);
}

IMULowpass::~IMULowpass() {
}


void IMULowpass::setSmoothingFactor(double smoothing_factor)
{
	if (smoothing_factor < 0.0)
		smoothing_factor = 0.0;
	if (smoothing_factor > 1.0)
		smoothing_factor = 1.0;
	smoothing_factor_ = smoothing_factor;
}

void IMULowpass::put(const VIOMeasurements &meas)
{
	if (first_time_)
	{
		filtered_meas_ = meas;
		first_time_ = false;
	} else {
		for (int i = 0; i < 3; i++)
		{
			filtered_meas_.acc_duo[i] = smoothing_factor_ * meas.acc_duo[i] + (1.0 - smoothing_factor_) * filtered_meas_.acc_duo[i];
			filtered_meas_.gyr_duo[i] = smoothing_factor_ * meas.gyr_duo[i] + (1.0 - smoothing_factor_) * filtered_meas_.gyr_duo[i];
		}
	}

}

void IMULowpass::get(VIOMeasurements &meas)
{
	meas = filtered_meas_;
}
