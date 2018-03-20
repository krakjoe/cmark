--TEST--
CommonMark\Node\OrderedList Start Negative
--FILE--
<?php
$list = new CommonMark\Node\OrderedList;

try {
	$list->start = -1;
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
