/* finance-enums.h
 *
 * Copyright 2020 galetedanilo <galetedanilo@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "finance-enum-types.h"

/**
 * FinanceTransaction:
 * @FINANCE_CREDIT:
 * @FINANCE_DEBIT:
 *
 * Enum with available transactions type
 */
typedef enum
{
  FINANCE_CREDIT,
  FINANCE_DEBIT,
} FinanceTransaction;

/**
 * FinanceRepeat:
 * @FINANCE_DAILY:
 * @FINANCE_MONDAY_FRIDAY:
 * @FINANCE_MONTHLY:
 * @FINANCE_NO_REPEAT:
 * @FINANCE_WEEKLY:
 * @FINANCE_YEARLY:
 *
 * Enum with available repetitions
 */
typedef enum
{
  FINANCE_DAILY,
  FINANCE_MONDAY_FRIDAY,
  FINANCE_MONTHLY,
  FINANCE_NO_REPEAT,
  FINANCE_WEEKLY,
  FINANCE_YEARLY,
} FinanceRepeat;

/**
 * FinanceFrequency:
 * @FINANCE_FOREVER:
 * @FINANCE_N_OCCURRENCES:
 * @FINANCE_UNTIL_DATE:
 *
 * Enum with available frequency
 */
typedef enum
{
  FINANCE_FOREVER,
  FINANCE_N_OCCURRENCES,
  FINANCE_UNTIL_DATE,
} FinanceFrequency;

/**
 * FinancePayment:
 * @FINANCE_CASH:
 * @FINANCE_CHECK:
 * @FINANCE_CREDIT_CARD:
 * @FINANCE_DEBIT_CARD:
 * @FINANCE_DEPOSIT:
 * @FINANCE_DIRECT_DEBIT:
 * @FINANCE_ELECTRONIC_PAYMENT:
 * @FINANCE_TRANSFER:
 *
 * Enum with available payments
 */
typedef enum
{
  FINANCE_CASH,
  FINANCE_CHECK,
  FINANCE_CREDIT_CARD,
  FINANCE_DEBIT_CARD,
  FINANCE_DEPOSIT,
  FINANCE_DIRECT_DEBIT,
  FINANCE_ELECTRONIC_PAYMENT,
  FINANCE_TRANSFER,
} FinancePayment;

/**
 * FinanceSymbol:
 * @FINANCE_INTERNATIONAL_SYMBOL:
 * @FINANCE_LOCAL_SYMBOL:
 *
 * Enum with available symbols
 */
typedef enum
{
  FINANCE_INTERNATIONAL,
  FINANCE_LOCAL,
} FinanceSymbol;


