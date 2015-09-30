#     When Harry Met Sally
#
#
# This program finds the earliest point at which Harry and Sally lived in the
# same city.
#
#  required output register usage:
#  $2: earliest year in same city
#
# 9/9/15                 John Pratt

.data
Harry:    .alloc  10                      # allocate static space for 5 moves
Sally:    .alloc  10                      # allocate static space for 5 moves

.text
WhenMet:  addi  $1, $0, Harry             # set memory base
          swi   586                       # create timelines and store them

Setup:    addi  $1, $0, 1986              # our year iterator
          addi  $2, $0, 0                 # current year index inside Harry
          addi  $3, $0, 4                 # current city index inside Harry
          addi  $4, $0, 0                 # current year index inside Sally
          addi  $5, $0, 4                 # current city index inside Sally
          lw    $6, Harry($2)             # Harry's lower year for current interval
          lw    $7, Sally($4)             # Sally's lower year for current interval

Loop:     slti  $8, $1, 2016              # $8 = year < 2016
          beq   $8, $0, Exit              # exit loop if $6 == false


          # determine if current year is between lowerHarry and upperSally
          slt   $8, $1, $6                # $8 = year < Harrylower
          nor   $8, $8, $8                # $8 = year >= Harrylower
          
          slt   $9, $1, $

          # now see if it is also between lowerSally and upperHarry

          # if it is, check the city ID's for the current blocks

          # if it is > upperSally, increment the sally counter, then check again



          # if it is > upperHarry, increment the Harry counter, then check again

          # if we find that the city ID's for the current year (overlapping time spans) match, we have the first meeting of the two, and can break the loop


Exit:     swi   587
          jr    $31                      # return to caller
