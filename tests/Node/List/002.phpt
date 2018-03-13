--TEST--
CommonMark\Node\OrderedList Tight Errors
--FILE--
<?php
$list = new CommonMark\Node\OrderedList;

try {
	$list->setTight([]);
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
