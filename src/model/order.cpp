/*
 * Order -- implementation
 *
 * TODO:
 *   - A flat 15% tax applies to every order. [Overview sec. 3]
 *   - Tax uses the full subtotal, before points or credit. [D1 p.3 Feature
 *     3]
 *   - Points can cover at most 50% of the pre-tax cost and never the tax; 1
 *     point = $1. [Overview sec. 3]
 *   - Earn 1 point per $3 paid, rounded down; none if any points were
 *     redeemed on the order; credit them when the order reaches Completed.
 *     [Overview sec. 3]
 *   - Amount charged = what is left after points and credit; the order is
 *     recorded as paid. [D1 p.3-4 Business Rules]
 */

#include "order.h"

Order::Order() = default;
