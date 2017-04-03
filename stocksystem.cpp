// File:        stocksystem.cpp
// Author:      BeiBei Li, Zisu Geng
// Description: implementation functions in stocksystem.h 

#pragma once 
#include "stocksystem.h"

// default constructor;
// begin with a balance of $100,000.00
StockSystem::StockSystem()
{
	balance = 100000.00;
}

// returns the balance member
double StockSystem::GetBalance()
{
	return balance;
}

// Add a new SKU to the system. Do not allow insertion of duplicate sku
bool StockSystem::StockNewItem(StockItem item)
{
	return records.Insert(item);
}

// Locate the item with key itemsku and update its description field.
// Return false if itemsku is not found.
bool StockSystem::EditStockItemDescription(unsigned int itemsku, string desc)
{
	StockItem item(itemsku, "", 0.00);
	StockItem* mod = records.Retrieve(item);

	if(mod==NULL)
	{return false;}

	return mod->SetDescription(desc);

}

// Locate the item with key itemsku and update its description field.
// Return false if itemsku is not found.
bool StockSystem::EditStockItemPrice(unsigned int itemsku, double retailprice)
{
	StockItem item(itemsku, "", 0.00);
	StockItem* mod = records.Retrieve(item);

	if(mod==NULL)
	{return false;}

	return mod->SetPrice(retailprice);


}

// Purchase quantity of item at unitprice each, to reach a maximum (post-purchase) on-hand stock quantity of 1000.
// Return false if balance is not sufficient to make the purchase,
//   or if SKU does not exist.
// Otherwise, return true and increase the item's on-hand stock by quantity,
//   and reduce balance by quantity*unitprice.
bool StockSystem::Restock(unsigned int itemsku, unsigned int quantity, double unitprice)
{
	StockItem item(itemsku, "", 0.00);
	StockItem* mod = records.Retrieve(item);

	if(mod==NULL)
	{return false;}

	if (quantity*unitprice >balance)
	{return false;}

	unsigned int currentAmount=mod->GetStock();
	if(currentAmount+quantity>1000)
	{
		quantity =1000-currentAmount;
	}

	balance = balance -	quantity*unitprice;
	return mod->SetStock(currentAmount+quantity);

}

// Sell an item to a customer, if quantity of stock is available and SKU exists.
// Reduce stock by quantity, increase balance by quantity*price, and return true if stock available.
// If partial stock (less than quantity) available, sell the available stock and return true.
// If no stock or sku does not exist, return false.
bool StockSystem::Sell(unsigned int itemsku, unsigned int quantity)
{
	StockItem item(itemsku, "", 0.00);
	StockItem* mod = records.Retrieve(item);

	if(mod==NULL)
	{return false;}

	unsigned int currentAmount=mod->GetStock();
	if(currentAmount==0)
	{return false;}

	if(quantity>currentAmount)
	{
		quantity=currentAmount;
	}
			
	balance = balance + quantity * (mod->GetPrice());
	return mod->SetStock(currentAmount - quantity);
			
	


}