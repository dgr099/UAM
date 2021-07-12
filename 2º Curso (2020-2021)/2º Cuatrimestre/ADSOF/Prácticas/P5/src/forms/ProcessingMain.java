package forms;

import java.io.IOException;

class Address implements java.lang.Comparable<Address>{
	private String address;
	private int postalCode;
	public Address(String adr, int pc) {
		this.address = adr;
		this.postalCode = pc;
	}
	public int postalCode() { return this.postalCode; }
	public String toString() {
		return this.address+" at PC("+this.postalCode+")";
	}
	@Override
	public int compareTo(Address arg0) {
		int dif = this.postalCode - arg0.postalCode;
		if(dif==0) {
			dif = this.address.compareTo(arg0.address);
		}
		return dif;
	}
}

public class ProcessingMain {
 public static void main(String[] args) throws IOException {
	 Form censusForm = new Form();
	 Field<Address> adr = new Field<Address>(s -> { String[] data = s.split(";");
	 	return new Address(data[0], Integer.valueOf(data[1].trim()));
	 }).
			 addValidation(a -> a.postalCode() >= 0, "Postal code should be positive");
	 Field<Integer> np = new Field<Integer>(s->Integer.valueOf(s)).
			 addValidation(s->s>0, "value greater than 0 expected");
	 censusForm.add("Enter address and postal code separated by ';'", adr).
	 add("Number of people living in that address?", np);
	 DataAggregator dag = new DataAggregator();
	 for (int i=0; i<3; i++)
		 dag.add(censusForm.exec());
	 System.out.println(dag);
 }
}