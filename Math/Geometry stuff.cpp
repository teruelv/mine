//find angle (P3, P1, P2)
ld angle(ii P1, ii P2, ii P3) {
    return atan2(P3.Y - P1.Y, P3.X - P1.X) -
           atan2(P2.Y - P1.Y, P2.X - P1.X)
}