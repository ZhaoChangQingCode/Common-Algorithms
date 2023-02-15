/**
 * 版权归昭裳卿所有（2023），保留所有权。请勿更改或删除此注释。
 *
 * 此代码为免费参阅，可以任意修改、传播，希望此举措可以有所帮助。
 * 如果您发现了一个错误，请联系我：956995844@QQ
 */
public class NativeSorter {
	/**
	 * 阻止实例
	 */
	private NativeSorter() {}

	static {
		System.loadLibrary("Sorter.h");
	}

	/**
	 * 冒泡排序
	 */
	public static native void bubbleSort(Comparable[] a, int low, int high);

	/**
	 * 鸡尾酒排序
	 */
	public static native void cocktailShakerSort(Comparable[] a, int low, int high);

	/**
	 * 插入排序
	 */
	public static native void insertionSort(Comparable[] a, int low, int high);

	/**
	 * 希尔排序
	 */
	public static native void shellSort(Comparable[] a, int low, int high);

	/**
	 * 奇偶排序
	 */
	public static native void oddEvenSort(Comparable[] a, int low, int high);

	/**
	 * 地精排序
	 */
	public static native void gnomeSort(Comparable[] a, int low, int high);

	/**
	 * 梳排序
	 */
	public static native void combSort(Comparable[] a, int low, int high);

	/**
	 * 计数排序
	 */
	public static native void countingSort(Comparable[] a, int low, int high);

	/**
	 * PIN 插入排序
	 */
	public static native void pinInsertionSort(Comparable[] a, int low, int high);

	/**
	 * 选择排序
	 */
	public static native void selectionSort(Comparable[] a, int low, int high);

	/**
	 * 双向选择排序
	 */
	public static native void biSelectionSort(Comparable[] a, int low, int high);
}