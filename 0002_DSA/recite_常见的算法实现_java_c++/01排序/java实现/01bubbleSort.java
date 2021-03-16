import java.util.Arrays;

public class BubbleSort {
    public static void main(String[] args) {
        int [] arr = {15,7,8,10,6,11,20,18};
        bubbleSort(arr,0,arr.length);
        System.out.println(Arrays.toString(arr));
    }
    public static void bubbleSort(int []arr,int low, int hi){
        if(low < 0 || hi > arr.length){
            return ;
        }
        int last = hi;
        while(last - low > 1){
            int scan_end = last;
            last = low;
            for(int i = low;i < scan_end-1;i++){
                if(arr[i] > arr[i+1]){
                    int t = arr[i];
                    arr[i] = arr[i+1];
                    arr[i+1] = t;
                    last = i+1;
                }
            }
        }

    }
}
