--TEST--
CommonMark\Node\OrderedList Delimiter Paren
--FILE--
<?php
$list = new CommonMark\Node\OrderedList;

$list->setDelimitParen();

if ($list->hasParenDelim()) {
	echo "OK";
}
?>
--EXPECT--
OK
