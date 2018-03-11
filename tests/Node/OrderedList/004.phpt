--TEST--
CommonMark\Node\OrderedList Start Negative
--FILE--
<?php
$list = new CommonMark\Node\OrderedList;

try {
	$list->setStart(-1);
} catch (InvalidArgumentException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
