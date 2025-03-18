\ Model (null)_copy
\ LP format - for model browsing. Use MPS format to capture full model detail.
\ Signature: 0x258268f64e24e0c0
Minimize
  q_1 + 0.1 W1_1 + 2 W2_1 + theta_2 + 50 Constant
Subject To
 R0: W1_1 <= 500
 R1: - q_1 - W0_1 + W1_1 + W2_1 = 50
 R2: theta_2 >= -2000
 R3: 0.1 W0_1 - 0.11 W1_1 - 0.3 W2_1 + theta_2 >= -1445
 R4: 11 q_1 + 0.21 W0_1 - 0.231 W1_1 - 0.63 W2_1 + theta_2 >= -884.5
 R5: 11.12234580384226 q_1 + 0.2234580384226492 W0_1
   - 0.2458038422649141 W1_1 - 0.6703741152679474 W2_1 + theta_2
   >= -821.4863498483317
Bounds
 theta_2 free
 Constant = 1
End
