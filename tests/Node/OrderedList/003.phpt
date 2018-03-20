--TEST--
CommonMark\Node\OrderedList Start Errors
--FILE--
<?php
$list = new CommonMark\Node\OrderedList;

try {
	$list->start = [];
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
