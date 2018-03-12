--TEST--
CommonMark\Node fetch Paragraph
--FILE--
<?php
$md = <<<MD
hello world
MD;

$parser = new CommonMark\Parser();

$parser->parse($md);

$doc = $parser->finish();

if ($doc->getFirstChild() instanceof CommonMark\Node\Paragraph) {
	echo "OK";
}
?>
--EXPECT--
OK
