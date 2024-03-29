/*
	Connorpog!

	Hoang, Connor
	Dang, Jeffrey
	Ly, Jenny
	Nguyen, Catherine
	Quach, Bryan

	December 2, 2021

	CS A250
	Project 1
*/

#include "DonorList.h"
#include "Database.h"

#include <iostream>
using namespace std;

// Node Class
Node::Node()
	: data(DonorType()), ptrToNext(nullptr) {}

Node::Node(DonorType newData, Node* newPtrToNext)
	: data(newData), ptrToNext(newPtrToNext) {}

Node* Node::getPtrToNext() const
{ 
	return ptrToNext; 
}

DonorType& Node::getData()
{
	return data;
}

void Node::setPtrToNext(Node* newPtrToNext)
{
	ptrToNext = newPtrToNext;
}

void Node::setData(DonorType newData) 
{ 
	data = newData; 
}

Node::~Node() {}

// DonorList Class
DonorList::DonorList()
	: first(nullptr), last(nullptr), count(0) {}

void DonorList::addDonor(const string& newFirst, 
	const string& newLast, int newNo, double newDonationAmt)
{
	DonorType newDonor(newFirst, newLast, newNo, newDonationAmt);
	if (count == 0)
	{
		first = new Node(newDonor, nullptr);
		last = first;
	}
	else
	{
		if (first->getData().getMembershipNo() > newNo)
		{
			first = new Node(newDonor, first);
		}
		else
		{
			Node* trailCurrent = first;
			Node* current = first->getPtrToNext();
			bool found = false;
			while (current != nullptr && !found)
			{
				if (current->getData().getMembershipNo() > newNo)
				{
					trailCurrent->setPtrToNext(new Node(
						newDonor, current));
					found = true;
				}
				else
				{
					trailCurrent = current;
					current = current->getPtrToNext();
				}
			}
			if (!found)
			{
				last->setPtrToNext(new Node(newDonor, nullptr));
				last = last->getPtrToNext();
			}
		}
	}
	count++;
}

void DonorList::createList()
{
	set<DonorType> donorSet = getData();
	if (donorSet.empty())
	{
		cout << "Database has no data.";
	}
	else
	{
		set<DonorType>::iterator it = donorSet.begin();

		while (it != donorSet.end())
		{
			addDonor(it->getFirstName(), it->getLastName(),
				it->getMembershipNo(), it->getAmountDonated());
			it++;
		}
	}
}

int DonorList::getNoOfDonors() const
{
	return count;
}

double DonorList::getTotalDonations() const
{
	double total = 0;

	Node* current = first;
	while (current != nullptr)
	{
		total += current->getData().getAmountDonated();
		current = current->getPtrToNext();
	}

	return total;
}

bool DonorList::isEmpty() const
{
	return (count == 0);
}

bool DonorList::searchID(int memberNo) const
{
	Node* current = first;
	bool found = false;

	while (current != nullptr && !found)
	{
		if (current->getData().getMembershipNo() == memberNo)
		{
			found = true;
		}
		current = current->getPtrToNext();
	}

	return found;
}

void DonorList::deleteDonor(int memberNo)
{
	//Check if it is first element
	if (first->getData().getMembershipNo() == memberNo)
	{
		if (first == last)
		{
			delete first;
			first = last = nullptr;
		}
		else
		{
			Node* current = first;
			first = first->getPtrToNext();
			delete current;
			current = nullptr;
		}
		--count;
		cout << "  => Donor has been deleted.\n";
	}
	//More than 1 element
	else
	{
		Node* trailCurrent = first;
		Node* current = first->getPtrToNext();
		bool found = false;

		while (current != nullptr && !found)
		{
			if (current->getData().getMembershipNo() == memberNo)
			{
				if (current == last)
				{
					last = trailCurrent;
				}
				trailCurrent->setPtrToNext(current->getPtrToNext());
				delete current;
				current = nullptr;
				--count;
				cout << "  => Donor has been deleted.\n";
				found = true;
			}
			else
			{
				trailCurrent = current;
				current = current->getPtrToNext();
			}
		}

		if (!found)
		{
			cout << "Donor is not in the list.\n";
		}
	}
}

void DonorList::printAllDonors() const
{
	Node* current = first;
	while (current != nullptr)
	{
		current->getData().MemberType::printMemberInfo();
		current = current->getPtrToNext();
	}

}

void DonorList::printAllDonations() const
{
	Node* current = first;
	while (current != nullptr)
	{
		current->getData().DonorType::printDonation();
		current = current->getPtrToNext();
	}
}

void DonorList::clearList()
{
	Node* temp = first;

	while (first != nullptr)
	{
		first = first->getPtrToNext();
		delete temp;
		temp = first;
	}

	last = nullptr;

	count = 0;
}

DonorList::~DonorList()
{
	clearList();
}
