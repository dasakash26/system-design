# Payment Gateway

---

## Functional Requirements

- **Client Management**: The system must support onboarding and managing multiple merchant clients.
- **Payment Methods**: The gateway must process transactions across diverse payment modes, specifically Credit/Debit Cards, Net Banking, and UPI.
- **Bank Integration**: The system must integrate with multiple acquiring banks (e.g., HDFC, ICICI, SBI) to facilitate the transactions.
- **Transaction Lifecycle**: The system must validate payment details and track the state of a transaction from initiation to completion, such as Pending, Success, or Failure.
- **Dynamic Routing**: The gateway must route transactions to specific banks based on configurable rules. Examples include routing all Credit Card transactions to a specific bank, or distributing UPI traffic using a percentage allocation between multiple banks.

---

## Happy Flow

- user clicks checkout
- merchant server -> processes the payment details -> send to the gateway
- gateway auth merchant -> a popup opens up at the user side -> user enters account details
- gateway receive the user details -> tokenises -> sends to the bank
- bank processes the user details , validates -> transfer to merchant

## Core Entities

- Merchant
- Transaction
- Payment Details
- Payment Gateway
- Payment Router
- Bank Adapter

## Class Design

class Merchant{
- id: string
- name: string
- apiKey: string
}

class Transaction{
- id: string
- merchetId: string
- customerId: string
- amount: number
- status: ('PENDING', 'SUCCESS', 'FAILED')
  --
+ Transaction(...) 
+ getStatus(): STAUS
}

class PaymentDetails{
- mode: ('UPI', 'CARD')
--
+ IPaymentDetails(mode: MODE)
+ getMode(): MODE
}

class CardPaymentDetails: PaymentDetails{
- tokenizedCardNo: string
- cardHoldersName: string
- expiaryDate: DateTime
- cardType: ('CREDIT', 'DEBIT')
--
CardPaymentDetails(...)
getCardType(): CARDTYPE
}

class UPIPaymentDetails: PaymentDetails{
- upiId: string
--
+ UPIPaymentDetails(...)
}

class IBankAdapter{
+ process: (payemntDetails: IPaymentDetails, transaction: Transaction): BankResponse
}

class SBIBankAdapter: IBankAdapter{
- bankApi
--
+ process: (payemntDetails: IPaymentDetails, transaction: Transaction): BankResponse
}

class BankResponse{
- success: boolean
- transactionId: string
- error: string
}

class IRouter{
+ route(payemntDetails: IPaymentDetails, transaction: Transaction): IBankAdapter
}

class PaymentGateway{
- router: IRouter
- merchantValidator
- paymentValidator
--
+ PaymentGateway(router: IRouter): void
+ processPayment(payemntDetails: IPaymentDetails, transaction: Transaction): STATUS
}

