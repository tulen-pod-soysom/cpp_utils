set term qt size 1600,900

set multiplot layout 2,2 columns
plot 'signal.txt' w l t "сигнал"
plot 'signal_abs.txt' w l t "АЧХ сигнала"
plot 'signal_ph.txt' w l t "ФЧХ сигнала"
plot 0

pause mouse close
unset multiplot