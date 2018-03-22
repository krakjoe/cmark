--TEST--
CommonMark\Node\OrderedList Start
--FILE--
<?php
$list = new CommonMark\Node\OrderedList;

$list->start = 4;

$f = function() use($list) {
	return $list->start;
};

if ($f() && $f() == 4) {
	echo "OK";
}
?>
--EXPECT--
OK
