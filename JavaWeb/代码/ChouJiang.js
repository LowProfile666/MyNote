
// each 循环遍历的意思
// $(".user .name") 选择器选择节点，它是一个节点集合。
// each(这里的函数被称为回调函数)
// jQuery库在调用这个回调函数的时候，会自动给这个回调函数传两个参数
// 第一个参数index（只是一个变量名）:index是元素的下标，下标从0开始，以1递增。
// 第二个参数item（只是一个变量名）：item代表的就是集合中的当前遍历到的元素。
//console.log(index)
// item 是dom节点（原生的JavaScript对象）。不是jquery对象。不能使用jQuery对象的方法/函数。
// 怎么把dom对象转换成jQuery对象。
// item是一个<a>标签对象，属于dom对象。dom对象有innerHTML/innerText属性，可以获取元素中文本内容。
// 大致的思路：将取到的用户名放到一个数组当中，然后生成随机数，随机数是数组的下标。
var arr = new Array()
$(".user .name").each(function(index, item){	
	//console.log(item.innerText)
	// 怎么把dom对象转换成jQuery对象呢？
	// $(dom对象) 就是一个jQuery对象
	// jQuery对象可以使用jQuery的方法/函数
	//console.log(index + "=" + $(item).text())
	arr.push($(item).text())
})

console.log(arr.join(","))

// 生成随机数，以随机数作为数组的下表
var myIndex = Math.round(Math.random() * arr.length)
console.log("中奖的老铁对应的数组下标：" + myIndex)
console.log("中奖的老铁是：" + arr[myIndex])