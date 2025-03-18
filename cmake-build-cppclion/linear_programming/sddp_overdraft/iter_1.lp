\ Model (null)_copy
\ LP format - for model browsing. Use MPS format to capture full model detail.
\ Signature: 0x324ac9d621847505
Minimize
  q_1 + 0.1 W1_1 + 2 W2_1 + theta_2 + 50 Constant
Subject To
 R0: W1_1 <= 500
 R1: - q_1 - W0_1 + W1_1 + W2_1 = 50
 R2: theta_2 >= -2000
Bounds
 theta_2 free
 Constant = 1
End
