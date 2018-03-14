Chloe wrote the first heuristic model for the Othello AI, finished the minimax
implementation, and completed alpha-beta pruning.

Katherine started the minimax implementation and tried to improve the heuristic
weighting.

Changes we made to the AI:
We added minimax and alpha-beta pruning implementation, so it is at least at a
competitive level. We are allowing our minimax to search up to 8 layers. Some
ideas that we tried but didn't work out include incorporating different weights
into the minimax implementation - intuitively, the corners are worth a lot more,
while the spaces next to the corners would be negatively weighted. Additionally, 
we could have taken into account the coin parity between the two players, mobility
(trying to maximize your own mobility and restrict opponent's), classifying
coins by their stability, and more heavily prioritizing corners captured. 

