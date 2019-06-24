// Uncomment the next lines for writing timing data to file
ofstream dat1;
dat1.open("timingsn10.dat",ios_base::app);
dat1 << setiosflags(ios::showpoint | ios::uppercase);
dat1 << setprecision(10) << setw(20) << timing << setprecision(10) << setw(20) << timing_arma << endl;
dat1.close();
ofstream dat1;
double analytic[n] = {3,7,11,15};
dat1.open("accuracy_rho_n200.dat",ios_base::app);
dat1 << setiosflags(ios::showpoint | ios::uppercase);
for (int i=0; i<4; i++){
  dat1 << setw(12) << setprecision(5) << eigenvalues[i]/analytic[i];
}
dat1 << endl;
dat1.close();
