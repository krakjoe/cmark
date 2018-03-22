--TEST--
CommonMark\Node\OrderedList Start Negative
--FILE--
<?php
$list = new CommonMark\Node\OrderedList;

$zero = 0;

try {
	$list->$zero;
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
