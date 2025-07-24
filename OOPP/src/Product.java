package assignment;

public abstract class Product {

	private String productName;
	private double productPrice;
	private int productQuantity, itemNumber;
	private boolean productStatus= true;
	
	public Product() {
		productStatus = true;
	}
	
	public Product(int itemNo, String productN, int productQ, double productP) {
		itemNumber = itemNo;
		productName = productN;
		productQuantity = productQ;
		productPrice = productP;
	}

	public String getProductName() {
		return productName;
	}

	public void setProductName(String productName) {
		this.productName = productName;
	}

	public double getProductPrice() {
		return productPrice;
	}

	public void setProductPrice(double productPrice) {
		this.productPrice = productPrice;
	}

	public int getProductQuantity() {
		return productQuantity;
	}

	public void setProductQuantity(int productQuantity) {
		this.productQuantity = productQuantity;
	}

	public int getItemNumber() {
		return itemNumber;
	}

	public void setItemNumber(int itemNumber) {
		this.itemNumber = itemNumber;
	}

	public boolean isProductStatus() {
		return productStatus;
	}

	public void setProductStatus(boolean productStatus) {
		this.productStatus = productStatus;
	}
	
	public double inventoryValue() {
		return productPrice * productQuantity;
	}
	
	// Do not allow the user to add stock to a discontinued product
	public void addQuantity(int productQ) {
		if(productStatus)
			productQuantity += productQ;
		else
			System.out.println("Not allow to add stock to a discontinued product.");
	}
	
	public void deductQuantity(int productQ) {
		productQuantity -= productQ;
	}
	
	@Override
	public String toString() {
		return "\nItem number\t: " + itemNumber + "\n" +
				"Product name\t: " + productName + "\n" +
				"Quantity available: " + productQuantity + "\n" +
				"Price (RM)\t: " + productPrice + "\n" +
				"Inventory value (RM):" + inventoryValue() + "\n" +
				"Product status: " + productStatus + "\n";
	}
	
}
