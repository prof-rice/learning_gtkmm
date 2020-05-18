For saving an Order to a stream, we simply need to write out all of the fields in our Order object to the stream in such a way that we can read them back in later using an Order constructor with an istream parameter. 

What fields matter in Order?  The email address, and the Product_orders!

So, line by line, we have this:

void Order::save(std::ostream& ost) {

To save the object, we call save with an output stream. That might be a file, or a string stream, or a network connection, or any other ostream.  Next, we write out the email. Note that we put a newline after each field that we write, which makes reloading them with getline really easy.

    ost << _email << '\n';

Now, we need to write out however many Product_orders there are in the vector _products. We have two options.
    • We could tell each Product_order in _products to save themselves to the stream, and then write a separate special line of text in the stream (e.g., "#end_of_product_orders") to signal that all have been loaded. However, that would take more code when loading the information. 
    • We could write out the number of elements in _products, so that the constructor below can just use a for or while loop to read them back in. Since we know before we start writing out Product_orders how many we have, it's simplest to write the quantity first, allowing us to use a simple while loop to add them to our _products vector, one construction at a time
So that gives us:

    ost << _products.size() << '\n';

Finally, we tell each of the elements of _products to save themselves to the stream. We expect Product_order's save method to follow the same logic as Order's logic that we're discussing here.

    for (auto& p : _products) p.save(ost);
}

---

For the constructor to recreate an order from an istream, let's first look at a couple of other Order methods in that code.

Order::Order(std::string email) : _email{email} { }

So to create an empty order, we just need to set an email address.  By implication, then, to restore a complete order from a stream, we'll need the email address. Now, having created an empty order, how would we add products to it? Using this method:

void Order::add_product_order(Product_order po) {
    _products.push_back(po);
}

So we'd need to create a Product_order and pass it to add_product_order to make it a part of that order.  But how do we create a new Product_order from a stream? Exactly the same way we create an Order from a stream - with a constructor using a stream as the parameter!

Product_order{ist}

As you can see, this strategy only works if we follow it all the way down to our non-dependent classes, who save and load primitives.

That brings us, then, to a line by line analysis of Order::Order(std::istream& ist).

Order::Order(std::istream& ist) {
    std::getline(ist, _email);

As above, first we need to read the email address into the _email field. Having load that into our under-construction Order, we can

    int products;
    ist >> products; ist.ignore();

This tells us how many Product_orders were in the original order, so that we know when to stop loading them. Given that, we can now use a countdown timer in a for or while loop (I chose the latter), constructing and pushing the Product_orders from the stream using Product_order's own istream-based constructor.

    while(products-- > 0) _products.push_back(Product_order{ist});
}

And there you have it. As long as each class implements its own istream-based constructor and ostream-based save method, you've successfully distributed the code for file I/O for a given field to the class actually containing that field. This is highly maintainable, I believe, and a simple pattern to follow for pretty much any object oriented application.
