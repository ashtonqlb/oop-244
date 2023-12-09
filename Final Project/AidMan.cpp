#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <cstring>

#include "AidMan.h"

#include <string>

#include "Perishable.h"
#include "Utils.h"

namespace sdds {

	AidMan::AidMan() : m_main_menu ("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database") {
		m_filename = nullptr;
	}

	AidMan::AidMan(const char* filename) : m_main_menu ("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database") {
		if (filename != nullptr) {
			m_filename = new char[strlen(filename) + 1];
			strcpy(m_filename, filename);
		} else m_filename = nullptr;
	}

	AidMan::~AidMan() {
		deallocate();
		delete[] m_filename;
	}

	unsigned int AidMan::menu() {
		int year, month, day = 0;
	
		ut.getSystemDate(&year, &month, &day);

		std::cout << "Aid Management System" << std::endl
				  << "Date: " << std::setw(4) << year << '/' << std::setfill('0') << std::setw(2) << month << '/' << std::setfill('0') << std::setw(2) << day << std::endl;
		std::cout << "Data file: " << (m_filename ? m_filename : "No file") << std::endl
				  << "---------------------------------" << std::endl;
		return m_main_menu.run();
	}

	void AidMan::run() {
	    unsigned int selection = 0;

	    do {
		    selection = menu();

	        if (selection != 0 && m_filename == nullptr && selection != 7) {
	            selection = 7;
	        }

			int user_selection;
			int max_quantity_change;
			int quantity_change;
			int matchingProducts;
			int choice_to_update;
			int index_to_update;
			int sku_to_update;
			iProduct* product_to_update;

	        switch (selection) {
	        case 1:
	            std::cout << "\n****List Items****\n";
				list();
	            break;

	        case 2:
				std::cout << "\n****Add Item****\n";
				if (m_products_stored >= sdds_max_num_items) {
					std::cout << "Database full!";
					break;
				}

				std::cout << "1- Perishable\n2- Non-Perishable\n-----------------\n0- Exit\n";
				std::cin.ignore(1000, '\n');

				user_selection = ut.get_int(0, 2, "> ");

				int sku_to_check;
	            const char* search_string;

				if (user_selection == 1) {
					sku_to_check = ut.get_int(1000, 39999, "SKU: ");
				}

				else if (user_selection == 2) {
					sku_to_check = ut.get_int(40000, 99999, "SKU: ");
				}
				
				else if (user_selection == 0) {
					std::cout << "Aborted\n";
					break;
				}

				else {
					std::cout << "Out of range error. Make a valid selection.\n";
					break;
				}

				if (search(sku_to_check) == -1) {
					iProduct* new_product;

					if (user_selection == 1) {
						new_product = new Perishable();
					}

					else {
						new_product = new Item();
					}

					std::cin.ignore(1000, '\n');
					new_product->read(std::cin);
					m_products[m_products_stored++] = new_product;
					save();
					std::cout << std::endl;
				} else {
					std::cout << "Sku: " << sku_to_check << " is already in the system, try updating quantity instead." << std::endl << std::endl;
				}
				break;


	        case 3:
	            std::cout << "\n****Remove Item****\n";

				std::cin.ignore(1000, '\n');	
				search_string = ut.get_cstring("Item description: ");

	        	if (list(search_string)) {
					std::cout << std::endl;
	        		sku_to_check = ut.get_int(10000, 99999, "Enter SKU: ");

	        		if (search(sku_to_check) > -1) {
						const int index = search(sku_to_check);

	        			std::cout << "Following item will be removed: " << std::endl;
						m_products[index]->display(std::cout) << std::endl;

						const int choice = ut.get_int(0, 1, "Are you sure?\n1- Yes!\n0- Exit\n> ");

						if (choice == 1) {
							remove(index);
							std::cout << "Item removed!\n\n";
						} else std::cout << "Aborted!\n\n";
	        		} else std::cout << "SKU Not found!";

					delete[] search_string;
					search_string = nullptr;
	        	} else std::cout << "No results found!";

	            break;
			case 4:
			    std::cout << "\n****Update Quantity****\n";
			    std::cin.ignore(1000, '\n');
	        	search_string = ut.get_cstring("Item description: ");

			    matchingProducts = list(search_string);

			    if (matchingProducts == 0) {
			        std::cout << "No matches found!\n";
			        delete[] search_string;
			        break;
			    }

				std::cout << '\n';
			    sku_to_update = ut.get_int(10000, 99999, "Enter SKU: ");
				index_to_update = search(sku_to_update);

			    if (index_to_update == -1) {
			        std::cout << "SKU not found!\n";
			        delete[] search_string;
			        break;
			    }

			    product_to_update = m_products[index_to_update];
			    std::cin.ignore(1000, '\n');
			    choice_to_update = ut.get_int(0, 2, "1- Add\n2- Reduce\n0- Exit\n> ");

			    if (choice_to_update == 0) {
			        std::cout << "Aborted!\n\n";
			        delete[] search_string;
			        break;
			    }

			    if (choice_to_update == 1) {
			        max_quantity_change = product_to_update->qtyNeeded() - product_to_update->qty();
			        if (max_quantity_change == 0) {
			            std::cout << "Quantity Needed already fulfilled!\n\n";
			            delete[] search_string;
			            break;
			        }
					std::cout << "Quantity to add: ";
			        quantity_change = ut.get_int(1, max_quantity_change);
			        m_products[index_to_update]->operator+=(quantity_change);
			        std::cout << quantity_change << " items added!\n\n";
			    }
			    else if (choice_to_update == 2) {
			        max_quantity_change = product_to_update->qty();
			        if (max_quantity_change == 0) {
			            std::cout << "Quantity on hand is zero!\n\n";
			            delete[] search_string;
			            break;
			        }
					std::cout << "Quantity to reduce: ";
			        quantity_change = ut.get_int(1, max_quantity_change);
			        m_products[index_to_update]->operator-=(quantity_change);
			        std::cout << quantity_change << " items removed!\n\n";
			    }
				save();
			    delete[] search_string;
				break;

	        case 5:
	            std::cout << "\n****Sort****\n";
				sort();
	            break;
	        case 6:
	            std::cout << "\n****Ship Items****\n";
				create_shipping_order(); // TODO: Write create_shipping_order method. This uses the same format as list but we output it to a file, with a title and today's date on top;
	            break;
	        case 7:
				std::cout << "\n****New/Open Aid Database****" << std::endl;
				std::cin.ignore(1000, '\n');
				delete[] m_filename;
				m_filename = ut.get_cstring("Enter file name: ");

				load();
				std::cout << m_products_stored << " records loaded!" << std::endl << std::endl; 
				break;

	        default:
	            break;
	        }

	    } while (selection != 0);

	    std::cout << "Exiting Program!\n";
	}

	void AidMan::save() const { 
	    if (m_filename != nullptr) {
	        std::ofstream ofstr(m_filename);

	        if (!ofstr) {
	            std::cerr << "Failed to open file " << m_filename << std::endl;
	            return;
	        }

	        for (int i = 0; i < m_products_stored; i++) {
				if (m_products[i]) {
					m_products[i]->save(ofstr);
				}
	        }
	    }
	}

	bool AidMan::load() {
		if(m_products[0]) {
			save();
			deallocate();
		}

	    if (m_filename != nullptr) {
		    std::ifstream ifstr(m_filename);

	        if (!ifstr) {
	            std::cerr << "Failed to open file " << m_filename << " for reading!" << std::endl;

	            std::cout << "Would you like to create a new data file?\n1- Yes!\n0- Exit" << std::endl;

				const int choice = ut.get_int(0, 1, "> ");

	            if (choice == 1) {
	                std::ofstream newFile(m_filename);
	                newFile.close();
	            }

	            return false;
	        }

	        while (ifstr.peek() != EOF) {
	        	char first_char = '\0';
	        	first_char = ifstr.peek();
	            iProduct* product = nullptr;

				if(first_char == '\n') {
					ifstr.ignore(1000, '\n');
					first_char = ifstr.peek();
				}

				switch (first_char) {
				    case '1':
				    case '2':
				    case '3':
				        product = new Perishable();
				    break;

				    case '4':
				    case '5':
				    case '6':
				    case '7':
				    case '8':
				    case '9':
				        product = new Item();
				    break;

					default:
						ifstr.setstate(std::ios::failbit);
				    break;
				}

                if (product) {
                    if (product->load(ifstr)) {
                        m_products[m_products_stored++] = product;
                    } else {
                        delete product;
                    }
                } else {
	                ifstr.setstate(std::ios::failbit);
	                break;
				}
	        }
	        ifstr.close();
	    }
	    return m_products_stored > 0;
	}

	int AidMan::list(const char* sub_desc) const {
	    int items_printed = 0;

	    std::cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << std::endl
	              << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;

	    for (int i = 0; i < m_products_stored; i++) {
	        iProduct* product = m_products[i];

	        if (sub_desc == nullptr || strstr(product->description(), sub_desc) != nullptr) {

	        	const char* description = product->description();
				char truncatedDesc[36];

				strncpy(truncatedDesc, description, 35);
				truncatedDesc[35] = '\0'; 

	            std::cout << std::setfill(' ') << std::setw(4) << i + 1 << " | "
	                      << std::setw(5) << product->sku() << " | "
	                      << std::setw(35) << std::left << truncatedDesc << " | " << std::right
	                      << std::setw(4) << product->qty() << " | "
	                      << std::setw(4) << product->qtyNeeded() << " | "
	                      << std::setw(7) << std::fixed << std::setprecision(2) << product->operator double() << " |";



	            if (product->expiry()) {
					if (product->handling_instructions() != nullptr) {
						std::cout << '*';
					} else {
						std::cout << ' ';
					}

	                std::cout << product->expiry();
	            }

	            std::cout << "\n";

	            items_printed++;
	        }
	    }

	    std::cout << "-----+-------+-------------------------------------+------+------+---------+-----------";

	    if (sub_desc == nullptr) {
	        std::cout << std::endl << "Enter row number to display details or <ENTER> to continue:" << std::endl << "> ";
	        char user_selection;
	        std::cin.ignore(1000, '\n');
	        std::cin.get(user_selection);

	        if (user_selection == '\n') {
	            std::cout << std::endl;
	            return items_printed;
	        }

	        if (std::isdigit(user_selection)) {
	            const int selected_row = user_selection - '0';

	            if (selected_row <= items_printed) {
	                const iProduct* selected_product = m_products[selected_row - 1];
	                selected_product->display(std::cout);
	                std::cout << std::endl << std::endl;
	            } else {
	                std::cout << "Invalid row number. Please enter a valid row number or <ENTER> to continue.\n";
	            }
	        } else {
	            std::cout << "Invalid input. Please enter a valid row number or <ENTER> to continue.\n";
	        }
	    }

	    if (items_printed == 0) {
	        std::cout << "The list is empty!\n";
	        return items_printed;
	    }

	    return items_printed;
	}

	int AidMan::search(const int sku) const {
		for (int i = 0; i < sdds_max_num_items; i++) {
			if (m_products[i] && m_products[i]->operator==(sku)) {
				return i;
			}
		}
		return -1;
	}

	void AidMan::sort() {
       for (int i = 0; i < m_products_stored - 1; ++i) {
            int max_id_x = i;
            for (int j = i + 1; j < m_products_stored; ++j) {
                if ((m_products[j]->qtyNeeded() - m_products[j]->qty()) > (m_products[max_id_x]->qtyNeeded() - m_products[max_id_x]->qty())) {
                    max_id_x = j;
                }
            }
            if (max_id_x != i) {
                // Swap m_products[i] and m_products[maxIdx]
                iProduct* temp = m_products[i];
                m_products[i] = m_products[max_id_x];
                m_products[max_id_x] = temp;
            }
        }
		save();
		std::cout << "Sort completed!\n\n";
	}

	void AidMan::remove(int index) {
		if (index < 0 || index > m_products_stored) {
	        std::cout << "Invalid index. No product removed." << std::endl;
	        return; 
		}

		delete m_products[index];

		for (int i = index; i < m_products_stored - 1; i++) {
			m_products[i] = m_products[i + 1];
		}

		m_products_stored--;
		save();
	}

	void AidMan::create_shipping_order() {
	    std::ofstream shipping_order_file("shippingOrder.txt");

	    if (!shipping_order_file) {
	        std::cerr << "Failed to create shippingOrder.txt file!" << std::endl;
	        return;
	    }

	    int year, month, day = 0;
	    ut.getSystemDate(&year, &month, &day);
	    shipping_order_file << "Shipping Order, Date: " << std::setw(4) << year << '/' << std::setfill('0') << std::setw(2) << month << '/' << std::setfill('0') << std::setw(2) << day << std::endl;

	    shipping_order_file << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << std::endl
	                       << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;

	    int shippedItems = 0;

	    for (int i = 0; i < m_products_stored; i++) {
	        iProduct* product = m_products[i];

				const char* description = product->description();
				char truncatedDesc[36];

				strncpy(truncatedDesc, description, 35);
				truncatedDesc[35] = '\0'; 

	        if (product->qtyNeeded() == product->qty()) {
	            shipping_order_file << std::setfill(' ') << std::setw(4) << shippedItems + 1 << " | "
	                                << std::setw(5) << product->sku() << " | "
	                                << std::setw(35) << std::left << truncatedDesc << " | " << std::right
	                                << std::setw(4) << product->qty() << " | "
	                                << std::setw(4) << product->qtyNeeded() << " | "
	                                << std::setw(7) << std::fixed << std::setprecision(2) << product->operator double() << " |";

	            if (product->expiry()) {
	                if (product->handling_instructions() != nullptr) {
	                    shipping_order_file << '*';
	                } else {
	                    shipping_order_file << ' ';
	                }
	                shipping_order_file << product->expiry();
	            }

	            shipping_order_file << "\n";

				remove(i);

	            shippedItems++;
	        }
	    }

	    shipping_order_file << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;
	    shipping_order_file.close();

		save();
	    std::cout << "Shipping Order for " << shippedItems << " times saved!\n\n";
	}

	void AidMan::deallocate() {
	    for (int i = 0; i < m_products_stored; i++) {
	        if (m_products[i] != nullptr) {
	            delete m_products[i];
	            m_products[i] = nullptr;
	        }
	    }
	    m_products_stored = 0;
	}
}
