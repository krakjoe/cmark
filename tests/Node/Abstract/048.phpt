--TEST--
CommonMark\Node cached object changed
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====

Hello World
EOD
);

$first = $doc->firstChild;

$first->unlink();

if ($doc->firstChild instanceof CommonMark\Node\Paragraph) {
	echo "OK";
}
?>
--EXPECT--
OK
