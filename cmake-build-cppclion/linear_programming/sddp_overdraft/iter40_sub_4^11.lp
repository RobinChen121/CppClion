\ Model (null)_copy
\ LP format - for model browsing. Use MPS format to capture full model detail.
\ Signature: 0x4b1a8453a133af5d
Minimize
  0 cash_4 - 0.5 I_4 + 10 B_4 - 160 Constant
Subject To
 R0: I_4 - B_4 = 1e+100
Bounds
 cash_4 free
 I_4 >= 1e+100
 B_4 = 0
 Constant = 1
End
