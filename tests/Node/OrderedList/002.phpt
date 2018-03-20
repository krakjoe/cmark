--TEST--
CommonMark\Node\OrderedList Start
--FILE--
<?php
$list = new CommonMark\Node\OrderedList;

$list->start = 4;

if ($list->start == 4) {
	echo "OK";
}
?>
--EXPECT--
OK
