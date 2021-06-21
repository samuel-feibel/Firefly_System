#ifndef ESTIMATESTATE_H
#define ESTIMATESTATE_H

void LatLonAlt2NED_Fcn(double Lat, double Lon, double Alt, double r0_ECEF, double NED_C_ECEF, double *r_NED);

void setAngle2Range(double *angle);

void setupP0ECEF();

void getMeasurementVector(double *Z, double *Z_input);

void LatLonAlt2ECEF_Fcn(double Lat, double Lon, double Alt, double *r0_ECEF);

static void TECEF2NED_Fcn(double r_ECEF, double *NED_C_ECEF);

void setupR0ECEF();

void estimateState(double *state);



#endif
