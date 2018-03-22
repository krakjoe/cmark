--TEST--
CommonMark\Node cached read string
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====

Hello World
EOD
);

if ($doc->firstChild->next->firstChild->literal == $doc->firstChild->next->firstChild->literal) {
	echo "OK";
}
?>
--EXPECT--
OK
