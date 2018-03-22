--TEST--
CommonMark\Node\OrderedList write error
--FILE--
<?php
$list = new CommonMark\Node\OrderedList;

try {
	$list->something = "NOT OKAY";
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
