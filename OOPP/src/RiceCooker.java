package assignment;

public class RiceCooker extends Product {
	private String cookingType;
	private String resolution;
	private int filledCapacity;

	public RiceCooker(int itemNo, String productName, int productQuantity, double productPrice, String type,
			String reslt, int capacity) {
		super(itemNo, productName, productQuantity, productPrice);
		cookingType = type;
		resolution = reslt;
		filledCapacity = capacity;
	}

	public String getCookingType() {
		return cookingType;
	}

	public void setCookingType(String cookingType) {
		this.cookingType = cookingType;
	}

	public String getResolution() {
		return resolution;
	}

	public void setResolution(String resolution) {
		this.resolution = resolution;
	}

	public int getFilledCapacity() {
		return filledCapacity;
	}

	public void setFilledCapacity(int filledCapacity) {
		this.filledCapacity = filledCapacity;
	}

	public double inventoryValue() {
		return getProductPrice() * getProductQuantity();
	}

	@Override
	public String toString() {
		return "\nItem number\t\t: " + getItemNumber() + "\n" + "Product name\t\t: " + getProductName() + "\n"
				+ "Cooker Type\t\t: " + cookingType + "\n" + "Resolution\t\t: " + resolution + "\n"
				+ "Volume (in litre)\t: " + filledCapacity + "\n" + "Quantity available\t: " + getProductQuantity()
				+ "\n" + "Price (RM)\t\t: " + getProductPrice() + "\n" + "Inventory value (RM): " + inventoryValue()
				+ "\n" + "Product status\t\t: " + isProductStatus() + "\n";
	}
}
