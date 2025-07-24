package assignment;

public class TV extends Product{
	
	private String screenType, resolution;
	private int displaySize;
	
	public TV(int itemNo, String productName, int productQuantity, double productPrice, String screenT, String resol, int size) {
		super(itemNo, productName, productQuantity, productPrice);
		screenType = screenT;
		resolution = resol;
		displaySize = size;
	}

	public String getScreenType() {
		return screenType;
	}

	public void setScreenType(String screenType) {
		this.screenType = screenType;
	}

	public String getResolution() {
		return resolution;
	}

	public void setResolution(String resolution) {
		this.resolution = resolution;
	}

	public int getDisplaySize() {
		return displaySize;
	}

	public void setDisplaySize(int displaySize) {
		this.displaySize = displaySize;
	}
	
	public double inventoryValue() {
		return getProductPrice() * getProductQuantity();
	}
	
	@Override
	public String toString() {
		return "\nItem number\t\t: " + getItemNumber() +  "\n" +
				"Product name\t\t: " + getProductName() +  "\n" +
				"Screen Type\t\t: " + screenType +  "\n" +
				"Resolution\t\t: " + resolution +  "\n" +
				"Display size\t\t: " + displaySize +  "\n" +
				"Quantity available\t: " + getProductQuantity() +  "\n" +
				"Price (RM)\t\t: " + getProductPrice() +  "\n" +
				"Inventory value (RM): " + inventoryValue() +  "\n" +
				"Product status\t\t: " + isProductStatus() + "\n";
	}
	
	
}

