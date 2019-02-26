/* Include the sbrk function */ 
#include <unistd.h> 
 
int has_initialized = 0;
void *managed_memory_start;
void *last_valid_address;
 
void m_malloc_init()
{ 
	 last_valid_address = sbrk(0);     
	 managed_memory_start = last_valid_address;     
	 has_initialized = 1;   
}
 
struct m_mem_control_block { 
	 int is_available; 
	 int size;
};
 
void m_free(void *firstbyte) { 
	 struct m_mem_control_block *m_mcb;  
	 m_mcb = firstbyte - sizeof(struct m_mem_control_block);   
	 m_mcb->is_available = 1;    
	 return;   
}  
 
void *m_malloc(long kolbytes) { 
	 void *current_location; 
	 struct m_mem_control_block *current_location_mcb;  
	 void *memory_location;  
	 if(! has_initialized)  { 
		m_malloc_init();
	 }
	 kolbytes = kolbytes + sizeof(struct m_mem_control_block);  
	 memory_location = 0;  
	 current_location = managed_memory_start;  
	 while(current_location != last_valid_address)  {
		 current_location_mcb = (struct m_mem_control_block *)current_location;
		 if(current_location_mcb->is_available){
			 if(current_location_mcb->size >= kolbytes){
				current_location_mcb->is_available = 0;
				memory_location = current_location;
				break;
	         }
		 }
	     current_location = current_location + 
	     current_location_mcb->size;
	 }
	 
	 if(! memory_location){
		 sbrk(kolbytes);
	     memory_location = last_valid_address;
	     last_valid_address = last_valid_address + kolbytes;
	     current_location_mcb = memory_location;
	     current_location_mcb->is_available = 0;
	     current_location_mcb->size = kolbytes;
	 }
	 memory_location = memory_location + sizeof(struct m_mem_control_block);
	 return memory_location;
 }
