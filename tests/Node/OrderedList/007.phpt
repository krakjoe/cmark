--TEST--
CommonMark\Node\OrderedList write cached start
--FILE--
<?php
$list = new CommonMark\Node\OrderedList;

$f = function($start) use($list) {
	return $list->start = $start;
};

if ($f(4) && $f(2) == 2) {
	echo "OK";
}
?>
--EXPECT--
OK
