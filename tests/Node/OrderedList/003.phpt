--TEST--
CommonMark\Node\OrderedList Start Errors
--FILE--
<?php
$list = new CommonMark\Node\OrderedList;

try {
	$list->setStart([]);
} catch (InvalidArgumentException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
