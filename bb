            C++/CSIM Simulation Report (Version 19.0 for Linux x86)

                           Fri Jun 16 14:52:52 2017


                     Ending simulation time:      3600.000
                     Elapsed simulation time:     3600.000
                     CPU time used (seconds):        0.000


FACILITY SUMMARY 

facility     service    service          through-    queue     response   compl
name           disc      time    util.     put       length      time     count
--------------------------------------------------------------------------------
update_work  fcfs       0.00000  0.000    0.00222    0.00000    0.00000        8
Floor[0]     fcfs       0.00000  0.000    0.00000   20.35778    0.00000        0
Floor[1]     fcfs       0.00000  0.000    0.00000   19.94359    0.00000        0
Floor[2]     fcfs       0.00000  0.000    0.00000   20.19629    0.00000        0
Floor[3]     fcfs       0.00000  0.000    0.00000   19.76440    0.00000        0
Floor[4]     fcfs       0.00000  0.000    0.00000   19.50720    0.00000        0
Floor[5]     fcfs       0.00000  0.000    0.00000   20.05005    0.00000        0
Floor[6]     fcfs       0.00000  0.000    0.00000   20.36227    0.00000        0
Floor[7]     fcfs       0.00000  0.000    0.00000   19.33662    0.00000        0
rest         fcfs      45.91495  0.038    0.00083    0.03826   45.91495        3
   > server  0         34.43621  0.019    0.00056                              2
   > server  1         68.87242  0.019    0.00028                              1



QTABLE 1:  car occupancy

      initial       0      minimum       0      mean                    0.000000
      final         0      maximum       0      variance                0.000000
      entries       0      range         0      standard deviation      0.000000
      exits         0                           coeff of variation      0.000000

                                             cumulative
        number    total time    proportion   proportion

             0    3600.00000     1.000000     1.000000   ********************
             1       0.00000     0.000000     1.000000                       

QTABLE 2:  car occupancy

      initial       0      minimum       0      mean                    0.000000
      final         0      maximum       0      variance                0.000000
      entries       0      range         0      standard deviation      0.000000
      exits         0                           coeff of variation      0.000000

                                             cumulative
        number    total time    proportion   proportion

             0    3600.00000     1.000000     1.000000   ********************
             1       0.00000     0.000000     1.000000                       

STATUS OF FACILITIES 

                busy     queue  
name.id        servers   length        processes
--------------------------------------------------------------------------------
update_work.6   0 of 1      0    serv: idle                                     
Floor[0].7      1 of 1     41    serv: dep_cust.17                              
                                queue: dep_cust.26   dep_cust.33   dep_cust.45  
                                       dep_cust.54   dep_cust.60   dep_cust.68  
                                       dep_cust.76   dep_cust.81   dep_cust.91  
                                       dep_cust.99   dep_cust.106  dep_cust.114 
                                       dep_cust.123  dep_cust.131  dep_cust.140 
                                       dep_cust.145  dep_cust.153  dep_cust.161 
                                       dep_cust.168  dep_cust.176  dep_cust.183 
                                       dep_cust.187  dep_cust.194  dep_cust.200 
                                       dep_cust.208  dep_cust.215  dep_cust.219 
                                       dep_cust.230  dep_cust.239  dep_cust.246 
                                       dep_cust.257  dep_cust.262  dep_cust.270 
                                       dep_cust.278  dep_cust.287  dep_cust.296 
                                       dep_cust.305  dep_cust.310  dep_cust.320 
                                       dep_cust.329  dep_cust.339               
Floor[1].8      1 of 1     41    serv: arr_cust.14                              
                                queue: arr_cust.22   arr_cust.29   arr_cust.36  
                                       arr_cust.43   arr_cust.50   arr_cust.62  
                                       arr_cust.69   arr_cust.77   arr_cust.85  
                                       arr_cust.95   arr_cust.104  arr_cust.112 
                                       arr_cust.121  arr_cust.128  arr_cust.136 
                                       arr_cust.144  arr_cust.150  arr_cust.160 
                                       arr_cust.169  arr_cust.177  arr_cust.185 
                                       arr_cust.195  arr_cust.204  arr_cust.213 
                                       arr_cust.221  arr_cust.228  arr_cust.235 
                                       arr_cust.244  arr_cust.250  arr_cust.258 
                                       arr_cust.269  arr_cust.274  arr_cust.282 
                                       arr_cust.288  arr_cust.299  arr_cust.307 
                                       arr_cust.313  arr_cust.319  arr_cust.326 
                                       arr_cust.334  arr_cust.342               
Floor[2].9      1 of 1     40    serv: arr_cust.16                              
                                queue: arr_cust.25   arr_cust.31   arr_cust.38  
                                       arr_cust.46   arr_cust.53   arr_cust.63  
                                       arr_cust.70   arr_cust.78   arr_cust.86  
                                       arr_cust.92   arr_cust.100  arr_cust.107 
                                       arr_cust.115  arr_cust.120  arr_cust.130 
                                       arr_cust.138  arr_cust.147  arr_cust.156 
                                       arr_cust.166  arr_cust.171  arr_cust.181 
                                       arr_cust.191  arr_cust.199  arr_cust.207 
                                       arr_cust.217  arr_cust.223  arr_cust.232 
                                       arr_cust.238  arr_cust.249  arr_cust.254 
                                       arr_cust.264  arr_cust.272  arr_cust.280 
                                       arr_cust.291  arr_cust.294  arr_cust.302 
                                       arr_cust.311  arr_cust.323  arr_cust.333 
                                       arr_cust.340                             
Floor[3].10     1 of 1     41    serv: arr_cust.18                              
                                queue: arr_cust.23   arr_cust.32   arr_cust.39  
                                       arr_cust.48   arr_cust.56   arr_cust.64  
                                       arr_cust.72   arr_cust.79   arr_cust.88  
                                       arr_cust.96   arr_cust.103  arr_cust.111 
                                       arr_cust.119  arr_cust.127  arr_cust.137 
                                       arr_cust.148  arr_cust.154  arr_cust.162 
                                       arr_cust.174  arr_cust.182  arr_cust.190 
                                       arr_cust.198  arr_cust.205  arr_cust.211 
                                       arr_cust.222  arr_cust.229  arr_cust.236 
                                       arr_cust.242  arr_cust.253  arr_cust.259 
                                       arr_cust.268  arr_cust.276  arr_cust.281 
                                       arr_cust.286  arr_cust.295  arr_cust.304 
                                       arr_cust.315  arr_cust.321  arr_cust.330 
                                       arr_cust.337  arr_cust.344               
Floor[4].11     1 of 1     41    serv: arr_cust.20                              
                                queue: arr_cust.28   arr_cust.40   arr_cust.47  
                                       arr_cust.55   arr_cust.61   arr_cust.71  
                                       arr_cust.80   arr_cust.87   arr_cust.94  
                                       arr_cust.102  arr_cust.110  arr_cust.118 
                                       arr_cust.126  arr_cust.134  arr_cust.142 
                                       arr_cust.152  arr_cust.159  arr_cust.165 
                                       arr_cust.170  arr_cust.180  arr_cust.186 
                                       arr_cust.193  arr_cust.202  arr_cust.210 
                                       arr_cust.218  arr_cust.227  arr_cust.237 
                                       arr_cust.245  arr_cust.251  arr_cust.261 
                                       arr_cust.267  arr_cust.277  arr_cust.285 
                                       arr_cust.293  arr_cust.298  arr_cust.303 
                                       arr_cust.312  arr_cust.318  arr_cust.327 
                                       arr_cust.336  arr_cust.345               
Floor[5].12     1 of 1     41    serv: arr_cust.13                              
                                queue: arr_cust.21   arr_cust.30   arr_cust.37  
                                       arr_cust.44   arr_cust.52   arr_cust.58  
                                       arr_cust.67   arr_cust.74   arr_cust.84  
                                       arr_cust.93   arr_cust.101  arr_cust.108 
                                       arr_cust.117  arr_cust.125  arr_cust.133 
                                       arr_cust.141  arr_cust.151  arr_cust.158 
                                       arr_cust.167  arr_cust.175  arr_cust.184 
                                       arr_cust.192  arr_cust.203  arr_cust.212 
                                       arr_cust.220  arr_cust.226  arr_cust.234 
                                       arr_cust.243  arr_cust.252  arr_cust.260 
                                       arr_cust.266  arr_cust.275  arr_cust.284 
                                       arr_cust.290  arr_cust.301  arr_cust.306 
                                       arr_cust.314  arr_cust.322  arr_cust.331 
                                       arr_cust.338  arr_cust.346               
Floor[6].13     1 of 1     41    serv: arr_cust.19                              
                                queue: arr_cust.27   arr_cust.35   arr_cust.42  
                                       arr_cust.49   arr_cust.57   arr_cust.65  
                                       arr_cust.75   arr_cust.83   arr_cust.89  
                                       arr_cust.98   arr_cust.109  arr_cust.116 
                                       arr_cust.122  arr_cust.129  arr_cust.135 
                                       arr_cust.143  arr_cust.149  arr_cust.155 
                                       arr_cust.163  arr_cust.173  arr_cust.178 
                                       arr_cust.188  arr_cust.196  arr_cust.201 
                                       arr_cust.209  arr_cust.216  arr_cust.225 
                                       arr_cust.231  arr_cust.240  arr_cust.247 
                                       arr_cust.256  arr_cust.263  arr_cust.273 
                                       arr_cust.283  arr_cust.292  arr_cust.297 
                                       arr_cust.308  arr_cust.316  arr_cust.325 
                                       arr_cust.332  arr_cust.341               
Floor[7].14     1 of 1     40    serv: arr_cust.15                              
                                queue: arr_cust.24   arr_cust.34   arr_cust.41  
                                       arr_cust.51   arr_cust.59   arr_cust.66  
                                       arr_cust.73   arr_cust.82   arr_cust.90  
                                       arr_cust.97   arr_cust.105  arr_cust.113 
                                       arr_cust.124  arr_cust.132  arr_cust.139 
                                       arr_cust.146  arr_cust.157  arr_cust.164 
                                       arr_cust.172  arr_cust.179  arr_cust.189 
                                       arr_cust.197  arr_cust.206  arr_cust.214 
                                       arr_cust.224  arr_cust.233  arr_cust.241 
                                       arr_cust.248  arr_cust.255  arr_cust.265 
                                       arr_cust.271  arr_cust.279  arr_cust.289 
                                       arr_cust.300  arr_cust.309  arr_cust.317 
                                       arr_cust.324  arr_cust.328  arr_cust.335 
                                       arr_cust.343                             
rest.53         2 of 2      0    serv: elevator.11   elevator.12                
                                                                                
